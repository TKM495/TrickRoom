#pragma once
#include "stdafx.h"

namespace basecross {
	class PlayerModel :public GameObject {
	public:
		PlayerModel(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		void OnCreate()override;
	};
}