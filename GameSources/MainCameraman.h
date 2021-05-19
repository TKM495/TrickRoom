#pragma once
#include "stdafx.h"

namespace basecross {
	class MainCameraman :public GameObject {
	public:
		MainCameraman(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate()override;
		void OnUpdate()override;
	};
}
//end basecross