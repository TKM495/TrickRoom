#pragma once
#include "stdafx.h"

namespace basecross {
	class FloorModel :public GameObject {
		shared_ptr<GameObject> m_floor;
	public:
		FloorModel(const shared_ptr<Stage>& stage,
			const shared_ptr<GameObject> floor)
			:GameObject(stage),
			m_floor(floor)
		{}

		void OnCreate()override;
		void OnUpdate()override;
		void OnCollisionEnter(shared_ptr<GameObject>& other) override;
		void OnCollisionExcute(shared_ptr<GameObject>& other) override;
	};
}