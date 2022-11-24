#include "Mine.h"

DAE::Mine::Mine()
{

}

DAE::Mine::~Mine()
{

}

void DAE::Mine::Initialize(b2World& world, b2Vec2 initialPosition, float radius)
{
	b2BodyDef def;
	def.type = b2BodyType::b2_staticBody;
	def.position = initialPosition;
	def.userData = this;

	m_pBody = world.CreateBody(&def);

	b2PolygonShape shape;
	// per shape a maximum of 8 vertices.
	std::array<b2Vec2, 8> vertices;
	for (int i = 0; i < vertices.size(); ++i) {
		float angle = (i *1.0f/ vertices.size()) * juce::MathConstants<float>::twoPi;
		vertices[i] = { radius * cos(angle), radius * sin(angle) };
	}
	shape.Set(vertices.data(), 8);

	b2FixtureDef fixture;
	fixture.friction = 0.8f;
	fixture.density = 1;
	fixture.shape = &shape;
	m_pBody->CreateFixture(&fixture);
}

b2Vec2 DAE::Mine::GetPosition() {
	return m_pBody->GetWorldCenter();
}

void DAE::Mine::Update(b2World& world) {

}
