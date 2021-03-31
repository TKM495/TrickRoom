/*!
@file pursuer.h
@brief ’Ç‚¢‚©‚¯‚Ä‚­‚é“G‚È‚Ç
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Pursuer : public GameObject
	{
		float m_Speed;
		void Move();
		Vec3 MoveVec();

	public:
		Pursuer(const std::shared_ptr<Stage>& stage)
			: GameObject(stage), m_Speed(2)
		{

		}

	public:
		void OnCreate() override;
		void OnUpdate() override;

	};
}