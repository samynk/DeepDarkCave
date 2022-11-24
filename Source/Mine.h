#pragma once

#pragma once
#include <JuceHeader.h>
#include "GameObject.h"

namespace DAE {
	class Mine : public  GameObject{
	public:
		Mine();
		~Mine();
		void Initialize(b2World& world, b2Vec2 initialPos,float radius);
		b2Vec2 GetPosition();
		void Update(b2World& world);
		int GetGameObjectType() override{
			return DAE::GameObject::MINE;
		}
	private:
		b2Body* m_pBody{ nullptr };
	};
}