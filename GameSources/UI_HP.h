#pragma once
#include "stdafx.h"

namespace basecross {
	class UI_HP : public GameObject
	{

		int hp;
		float count;
		bool bActive;
		std::vector<std::shared_ptr<Numbers>> numbers;

	public:
		UI_HP(const std::shared_ptr<Stage>& stage)
			: GameObject(stage), hp(5), count(0.0f), bActive(false)
		{

		}

		void OnCreate() override;
		void OnUpdate() override;
		void OnDraw() override;

		void FadeIn();
	};
}