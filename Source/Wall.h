#pragma once
#include <JuceHeader.h>
#include "GameObject.h"

namespace DAE {
	class Wall : public GameObject {
	public:
		Wall() {

		}
		~Wall() {

		}
		void Initialize(b2World& world, b2Vec2 initialPos, b2Vec2 size,float orientation);

		b2Vec2 GetPosition();

		void Update(b2World& world);

		int GetGameObjectType() override;
	private:
		b2Body* m_pBody{ nullptr };
	};
}