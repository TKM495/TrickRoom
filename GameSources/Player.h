/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"
//#include "InputHandler.h"

namespace basecross{
	class Player : public GameObject {

		//InputHandler<Player> m_InputHandler;

		Vec3 m_Speed;//�ړ�
		int m_HP;//HP(�����l�T)
		float m_crystal;

		//HP
		void SetHP(int HP);
		int GetHP();
		//Crystal
		float GetCrystal();


		
		//Vec3 jumpVelocity;

	//private: bool bJump = false;

	public:
		Player(const std::shared_ptr<Stage>& stage) 
			: GameObject(stage),m_HP(5),m_crystal(0)
		{

		}

		void OnCreate() override;
		void OnUpdate() override;
		void SetSpeed();


		//void OnPushA();
		//void OnPushB(){}
		//void OnPushX() {}
		//void OnPushY() {}
		//void OnPushStart(){}
		//void OnPushBack() {}

	};
}
//end basecross

