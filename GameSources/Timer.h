#pragma once
#include "stdafx.h"

namespace basecross {
	class Timer : public GameObject
	{

		int timer;
		float count;

		std::vector<std::shared_ptr<Numbers>> numbers;

	public:
		Timer(const std::shared_ptr<Stage>& stage)
			: GameObject(stage), timer(180), count(0.0f)
		{

		}

		void OnCreate() override;
		void OnUpdate() override;
		void OnDraw() override;
	};
}