#pragma once
#include "stdafx.h"

namespace basecross {
	class UI_HP : public GameObject
	{

		int hp;
		float count;

		std::vector<std::shared_ptr<Numbers>> numbers;

	public:
		UI_HP(const std::shared_ptr<Stage>& stage)
			: GameObject(stage), hp(5), count(0.0f)
		{

		}

		void OnCreate() override;
		void OnUpdate() override;
		void OnDraw() override;
	};
}