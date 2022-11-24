#include "Wall.h"

void DAE::Wall::Initialize(b2World& world, b2Vec2 initialPos, b2Vec2 size, float orientation)
{
	b2BodyDef def;
	def.type = b2BodyType::b2_staticBody;
	def.position = initialPos;
	def.angle = orientation;
	def.userData = this;

	auto body = world.CreateBody(&def);

	b2PolygonShape shape;
	shape.SetAsBox(size.x,size.y);

	b2FixtureDef fixture;
	fixture.friction = 0.8f;
	fixture.density = 1;
	fixture.shape = &shape;
	body->CreateFixture(&fixture);
}

b2Vec2 DAE::Wall::GetPosition() {
	return m_pBody->GetWorldCenter();
}

void DAE::Wall::Update(b2World& world) {

}

int DAE::Wall::GetGameObjectType() {
	return GameObject::WALL;
}