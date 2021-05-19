#pragma once
#include "stdafx.h"

namespace basecross {
	class Bullet : public GameObject
	{
		static int count;
		float m_speed;
	public:
		Bullet(const shared_ptr<Stage>& stage)
			: GameObject(stage),
			m_speed(7.0f)
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