/*!
@file Player.h
@brief “G‚È‚Ç
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Enemy : public GameObject {
		float m_TotalTime;
		Vec3 m_Position;

	public:
		Enemy(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
		{}

		void OnCreate() override;
		void OnUpdate() override;
	};

}