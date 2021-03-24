/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"
//#include "InputHandler.h"

namespace basecross{
	class Player : public StageObject {

		//InputHandler<Player> m_InputHandler;

		Vec3 m_Speed;//�ړ�
		float m_moveSpeed;
		int m_HP;//HP(�����l�T)
		float m_crystal;

		float m_count;
		float m_RespawnTime;
		bool bRespawn;

		void Respawn();
		void Move();

	public:
		//HP
		void SetHP(int HP);
		int GetHP();
		//Crystal
		float GetCrystal();


		
		//Vec3 jumpVelocity;
		//private: bool bJump = false;
	public:
		Player(const std::shared_ptr<Stage>& stage,
			const wstring& line);

		void OnCreate() override;
		void OnUpdate() override;
		void SetSpeed();

		//HP
		void SetHP(int HP);
		int GetHP();
		//Crystal
		float GetCrystal();
		void OnCollisionEnter(std::shared_ptr<GameObject>& other) override;

		//void OnPushA();
		//void OnPushB(){}
		//void OnPushX() {}
		//void OnPushY() {}
		//void OnPushStart(){}
		//void OnPushBack() {}

	};
}
//end basecross

