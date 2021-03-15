/*!
@file Player.h
@brief ƒvƒŒƒCƒ„[‚È‚Ç
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Player : public GameObject {
		Vec3 m_Speed;
	public:
		Player(const std::shared_ptr<Stage>& stage) 
			: GameObject(stage)
		{

		}

		void OnCreate() override;
		void OnUpdate() override;
		void SetSpeed();
	};
}
//end basecross

