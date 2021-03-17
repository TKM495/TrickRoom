/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"
#include "InputHandler.h"

namespace basecross{
	class Player : public GameObject {

		InputHandler<Player> m_InputHandler;

		Vec3 m_Speed;//�ړ�


	public:
		Player(const std::shared_ptr<Stage>& stage) 
			: GameObject(stage)
		{

		}

		void OnCreate() override;
		void OnUpdate() override;
		void SetSpeed();

		void OnPushA();
		void OnPushB(){}
		void OnPushX() {}
		void OnPushY() {}
		void OnPushStart(){}
		void OnPushBack() {}

	};
}
//end basecross

