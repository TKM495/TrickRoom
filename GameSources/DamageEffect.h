#pragma once
#include "stdafx.h"

namespace basecross
{
	class DamageEffect : public GameObject
	{
		static int count;

		float deg;
		float jumpforce;
		bool bBullet;

	public:
		DamageEffect(const std::shared_ptr<Stage>& stage)
			:GameObject(stage), deg(0.0f), jumpforce(0.2f), bBullet(true)
		{

		}

		void OnCreate() override;
		void OnUpdate() override;

		static int getCount()
		{
			return count;
		}
	};
}