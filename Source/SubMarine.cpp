#include "SubMarine.h"
#include "GameObject.h"

DAE::SubMarine::SubMarine()
{

}

DAE::SubMarine::~SubMarine()
{
}

b2Vec2 DAE::SubMarine::GetPosition() {
	return m_pBody->GetPosition();
}

void DAE::SubMarine::Initialize(b2World& world)
{
	b2BodyDef def;
	def.type = b2BodyType::b2_dynamicBody;
	def.gravityScale = 0.1;
	def.position = { 100,250 };
	def.userData = this;

	m_pBody = world.CreateBody(&def);

	b2MassData md;
	md.mass = 5;
	md.center = { 0,0 };
	m_pBody->SetMassData(&md);

	// counter clock wise direction.
	b2PolygonShape shape2;
	std::array<b2Vec2, 5> vertices;
	vertices[4] = { -25,8 };
	vertices[3] = { 25,8 };
	vertices[2] = { 30,0 };
	vertices[1] = { 25,-8 };
	vertices[0] = {-25,-8};
	shape2.Set(vertices.data(), vertices.size());

	b2FixtureDef fixture2;
	fixture2.friction = 0.8f;
	fixture2.density = 1;
	fixture2.shape = &shape2;
	// bounciness
	fixture2.restitution = 0.01f;
	m_pBody->CreateFixture(&fixture2);
}

void DAE::SubMarine::Update(b2World& world) {
	using namespace juce;
	if (KeyPress::isKeyCurrentlyDown(KeyPress::spaceKey)) {
		m_pBody->ApplyLinearImpulse(b2Vec2(0, -1000), m_pBody->GetWorldCenter());
	}
	
}



int DAE::SubMarine::GetGameObjectType() {
	return GameObject::SUBMARINE;
}
