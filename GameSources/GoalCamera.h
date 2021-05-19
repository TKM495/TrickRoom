#pragma once
#include "stdafx.h"
#include "MainCamera.h"

namespace basecross {
	class GoalCamera :public Camera {
	public:
		GoalCamera()
		{}

		void OnCreate()override;
		void OnUpdate()override {};

		state GetCamState() {
			return state::Right;
		}

		bool GetbLeapFlg() {
			return false;
		}
	};
}
//end basecross