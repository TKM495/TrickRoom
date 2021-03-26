/*!
@file Player.h
@brief
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"
//#include "InputHandler.h"

namespace basecross {
	class Player : public StageObject {

		//InputHandler<Player> m_InputHandler;

		float m_moveSpeed;
		int m_HP;
		float m_crystal;

		//Respawn
		//float m_count;
		//float m_RespawnTime;
		//bool bRespawn;

		//void Respawn();

		void Move();
		Vec3 MoveVec();

	public:
		//HP
		void SetHP(int HP);
		int GetHP();
		//Crystal
		int GetCrystal();


		//Vec3 jumpVelocity;

	//private: bool bJump = false;


		//Vec3 jumpVelocity;
		//private: bool bJump = false;
	public:
		Player(const std::shared_ptr<Stage>& stage,
			const wstring& line);

		void OnCreate() override;
		void OnUpdate() override;
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

