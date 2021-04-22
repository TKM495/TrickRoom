#pragma once
#include "stdafx.h"
#include <Numbers.h>

namespace basecross {
	class Timer_1 : public GameObject
	{
		int timer;
		int bup;
		float count;

		std::vector<std::shared_ptr<Numbers>> numbers;

	public:
		Timer_1(const std::shared_ptr<Stage>& stage)
			: GameObject(stage), timer(0), count(0.0f), bup(false)
		{

		}

		void OnCreate() override;
		void OnUpdate() override;

		void OnDraw() override;

		void Start();
		void Stop();

		//Getter(タイマーの値を返すやつ)
		float GetTime();
	};
}