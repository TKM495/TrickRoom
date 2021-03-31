#pragma once
#include "stdafx.h"
#include <Numbers.h>

namespace basecross {
	class Score : public GameObject
	{
		int score;
		std::vector<std::shared_ptr<Numbers>> numbers;

	public:
		Score(const std::shared_ptr<Stage>& stage)
			: GameObject(stage), score(0)
		{
		}

		void OnCreate() override;
		void OnUpdate() override;
		void OnDraw() override;
	};
}