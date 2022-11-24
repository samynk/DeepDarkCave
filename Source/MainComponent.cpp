#include "MainComponent.h"
#include "GameObject.h"

//==============================================================================
MainComponent::MainComponent()
{
	// Make sure you set the size of the component after
	// you add any child components.
	setSize(800, 600);
	setFramesPerSecond(60); // This sets the frequency of the update calls.

	auto currentDir = juce::File::getCurrentWorkingDirectory();
	juce::Logger::writeToLog(
		juce::String("current working directory : ") 
		+ currentDir.getFileName());

	/*b2BodyDef def2;
	def2.type = b2BodyType::b2_dynamicBody;
	def2.position = { 300,100 };
	def2.angularVelocity = 0;



	auto body2 = m_World.CreateBody(&def2);

	b2MassData md;
	md.mass = 5;
	body2->SetMassData(&md);

	b2PolygonShape shape2;
	shape2.SetAsBox(5, 5);

	b2FixtureDef fixture2;
	fixture2.friction = 0.8f;
	fixture2.density = 1;
	fixture2.shape = &shape2;
	fixture2.restitution = 0.8f;
	fixture2.userData = nullptr;
	body2->CreateFixture(&fixture2);*/

	m_SubMarine.Initialize(m_World);

	for (int i = 0; i < m_Mines.size(); ++i)
	{
		float x = (r.nextFloat()-.5f) * 500 + 100;
		float y = (r.nextFloat()-.5f) * 500 + 200;
		m_Mines[i].Initialize(m_World, { x,y }, 25);
	}

	m_Walls[0].Initialize(m_World, { 100,300 }, { 100,10 }, 0.1f);
	m_Walls[1].Initialize(m_World, { 270,320 }, { 100,10 }, -0.2f);

	m_World.SetContactListener(this);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::update()
{
	// This function is called at the frequency specified by the setFramesPerSecond() call
	// in the constructor. You can use it to update counters, animate values, etc.
	m_World.Step(1.0f / 60, 6, 2);

	using namespace juce;
	if (KeyPress::isKeyCurrentlyDown(KeyPress::leftKey)) {
		m_CamPos.x -= 1;
	}
	if (KeyPress::isKeyCurrentlyDown(KeyPress::rightKey)) {
		m_CamPos.x += 1;
	}
	if (KeyPress::isKeyCurrentlyDown(KeyPress::upKey)) {
		m_CamPos.y -= 1;
	}
	if (KeyPress::isKeyCurrentlyDown(KeyPress::downKey)) {
		m_CamPos.y += 1;
	}
	m_SubMarine.Update(m_World);

	if (KeyPress::isKeyCurrentlyDown(KeyPress::backspaceKey)) {
		juce::Logger::writeToLog(juce::String("RayCasting "));
		auto rayStart = m_SubMarine.GetPosition();
		m_World.RayCast(this, rayStart, rayStart + b2Vec2{200, 0});
	}
}

//==============================================================================
void MainComponent::paint(juce::Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
	juce::Box2DRenderer renderer;
	juce::Rectangle<float> targetArea{ 0, 0, 800, 600 };
	b2Vec2 camPos = m_SubMarine.GetPosition();
	renderer.render(g, m_World, camPos.x-400, camPos.y-300, camPos.x + 400, camPos.y + 300, targetArea);

	juce::Line<float> line{ 400,300,400 + 100 * cos(m_Angle),300 + 100 * sin(m_Angle) };
	g.drawArrow(line, 2, 10, 30);
}


void MainComponent::BeginContact(b2Contact* contact) {
	juce::Logger::writeToLog("Begin Contact");
	//check game object type of fixture A
	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	int typeA = -1;
	if ( bodyUserDataA != nullptr ) {
		
		DAE::GameObject* go = static_cast<DAE::GameObject*>(bodyUserDataA);
		typeA = go->GetGameObjectType();
		switch (typeA)
		{
		case DAE::GameObject::SUBMARINE:
			juce::Logger::writeToLog("Collision start of Submarine ");
			break;
		}
	}

	//check game object type of fixture B
	void *bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
	int typeB = -1;
	if (bodyUserDataB != nullptr)
	{
		DAE::GameObject* goB = (DAE::GameObject*)bodyUserDataB;
		typeB = goB->GetGameObjectType();
		switch (typeB)
		{
		case DAE::GameObject::SUBMARINE:
			juce::Logger::writeToLog("with another SubMarine.\n");
			break;
		case DAE::GameObject::WALL:
			juce::Logger::writeToLog("with the wall.\n");
			break;
		case DAE::GameObject::MINE:
			juce::Logger::writeToLog("with a mine.\n");
			break;
		}
	}
	//take typeA and typeB into account to start sound
}

void MainComponent::EndContact(b2Contact* contact) {
	juce::Logger::writeToLog("End Contact");
	//check game object type of fixture A
	void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserDataA != nullptr) {

		DAE::GameObject* go = (DAE::GameObject*)bodyUserDataA;
		switch (go->GetGameObjectType())
		{
		case DAE::GameObject::SUBMARINE:
			juce::Logger::writeToLog("Collision end of Submarine with");
			break;
		}
	}

	//check game object type of fixture B
	void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserDataB != nullptr)
	{
		DAE::GameObject* goB = (DAE::GameObject*)bodyUserDataB;
		switch (goB->GetGameObjectType())
		{
		case DAE::GameObject::SUBMARINE:
			juce::Logger::writeToLog("with another SubMarine");
			break;
		case DAE::GameObject::WALL:
			juce::Logger::writeToLog("with the wall");
			break;
		case DAE::GameObject::MINE:
			juce::Logger::writeToLog("with a mine");
			break;
		}
	}

}

float32  MainComponent::ReportFixture(b2Fixture* fixture,
	const b2Vec2& point,
	const b2Vec2& normal,
	float32 fraction)
{
	void* userData = fixture->GetBody()->GetUserData();
	if (userData != nullptr) {
		DAE::GameObject* go = (DAE::GameObject*)userData;
		if (go->GetGameObjectType() == DAE::GameObject::MINE)
		{
			juce::Logger::writeToLog(juce::String("Mine found at  : ") + juce::String(point.x) + " , " + juce::String(point.y));
			return 0;
		}
		else if (go->GetGameObjectType() == DAE::GameObject::WALL)
		{
			juce::Logger::writeToLog(juce::String("Wall found at  : ") + juce::String(point.x) + " , " + juce::String(point.y));
			return 0;
		}
		return 0;
	}
}

void MainComponent::resized()
{
	// This is called when the MainContentComponent is resized.
	// If you add any child components, this is where you should
	// update their positions.
}
