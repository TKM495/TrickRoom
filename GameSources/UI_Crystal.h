#pragma once
#include "stdafx.h"

namespace basecross {
	class UI_Crystal : public GameObject
	{

		int point;
		bool bActive;

		std::vector<std::shared_ptr<Numbers>> numbers;

	public:
		UI_Crystal(const std::shared_ptr<Stage>& stage)
			: GameObject(stage), point(0), bActive(false)
		{

		}

		void OnCreate() override;
		void OnUpdate() override;
		void OnDraw() override;

		void FadeIn();
	};
}