/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Player : public GameObject {

		float m_moveSpeed;
		int m_HP;//HP(初期値５)
		float m_crystal;
		//float m_count;//Respawn
		//float m_RespawnTime;
		//bool bRespawn;
		bool bMutekiFlg;
		float m_Mcount;
		float m_MTime;

		int m_DrawCount;
		uint8_t m_BlinkMask;


		//void Respawn();
		void Move();
		Vec3 MoveVec();
		void Muteki();

	public:
		//HP
		void SetHP(int HP);
		int GetHP();
		//Crystal
		int GetCrystal();

		void Draw();


	public:
		Player(const std::shared_ptr<Stage>& stage)
			: GameObject(stage), m_moveSpeed(3), m_HP(5), m_crystal(0), bMutekiFlg(false), m_Mcount(0), m_MTime(2), m_DrawCount(0), m_BlinkMask(8)
			/*,m_count(0),m_RespawnTime(2),bRespawn(false)*/
		{

		}

		void OnCreate() override;
		void OnUpdate() override;
		void OnCollisionEnter(std::shared_ptr<GameObject>& other) override;

	};
}
//end basecross

