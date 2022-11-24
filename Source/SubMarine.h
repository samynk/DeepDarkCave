#pragma once
#include <JuceHeader.h>
#include "GameObject.h"

namespace DAE {
	class SubMarine : public GameObject {
	public:
		SubMarine();
		~SubMarine();
		void Initialize(b2World& world);
		b2Vec2 GetPosition();
		void Update(b2World& world);
		

		int GetGameObjectType() override;
	private:
		b2Body* m_pBody{ nullptr };
	};
}
