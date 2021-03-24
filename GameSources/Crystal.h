#pragma once
#include "stdafx.h"

namespace basecross {
	class Crystal : public GameObject
	{

		int point;

		std::vector<std::shared_ptr<Numbers>> numbers;

	public:
		Crystal(const std::shared_ptr<Stage>& stage)
			: GameObject(stage), point(0)
		{

		}

		void OnCreate() override;
		void OnUpdate() override;
		void OnDraw() override;
	};
}