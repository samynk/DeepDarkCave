#pragma once

namespace DAE {
	class GameObject {
	public:
		virtual int GetGameObjectType() = 0;

		// add other types of objects here.
		static const int MINE = 0;
		static const int SUBMARINE = 1;
		static const int WALL = 2;
	};
}
