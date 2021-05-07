#pragma once
#include "stdafx.h"

namespace basecross {
	class StartPoint :public GameObject {
		float m_size;
		Vec3 m_position;
	public:
		StartPoint(const shared_ptr<Stage>& stage,
			const Vec3& pos)
			:GameObject(stage), m_size(2.0f), m_position(pos)
		{}

		void OnCreate()override;
	};
}
//end basecross