#pragma once
#include "stdafx.h"

namespace basecross {
	class HP : public GameObject
	{

		int hp;
		float count;

		std::vector<std::shared_ptr<Numbers>> numbers;

	public:
		HP(const std::shared_ptr<Stage>& stage)
			: GameObject(stage), hp(5), count(0.0f)
		{

		}

		void OnCreate() override;
		void OnUpdate() override;
		void OnDraw() override;
	};
}