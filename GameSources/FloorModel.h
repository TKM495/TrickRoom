#pragma once
#include "stdafx.h"
#include "RouteFloor.h"

namespace basecross {
	class FloorModel :public GameObject {
		shared_ptr<RouteFloor> m_floor;
	public:
		FloorModel(const shared_ptr<Stage>& stage,
			const shared_ptr<RouteFloor> floor)
			:GameObject(stage),
			m_floor(floor)
		{}

		void OnCreate()override;
		void OnUpdate()override;
		void OnCollisionEnter(shared_ptr<GameObject>& other) override;
		void OnCollisionExcute(shared_ptr<GameObject>& other) override;
	};
}