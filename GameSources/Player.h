/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"
//#include "InputHandler.h"

namespace basecross {
	class Player : public GameObject {

		//InputHandler<Player> m_InputHandler;

		float m_moveSpeed;
		int m_HP;//HP(初期値５)
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


	public:
		Player(const std::shared_ptr<Stage>& stage)
			: GameObject(stage), m_moveSpeed(5), m_HP(5), m_crystal(0)
			/* m_count(0), m_RespawnTime(2), bRespawn(false)*/
		{

		}

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

