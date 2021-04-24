#pragma once
#include "stdafx.h"

namespace basecross {
	class Bullet : public GameObject
	{
		static int count;

	public:
		Bullet(const shared_ptr<Stage>& stage)
			: GameObject(stage)
		{
			count++;
		}

		virtual ~Bullet()
		{
			count--;
		}

		void OnCreate() override;
		void OnUpdate() override;
		void OnCollisionEnter(shared_ptr<GameObject>& other) override;

		static int getCount()
		{
			return count;
		}
	};
}