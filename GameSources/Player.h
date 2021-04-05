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
		Vec3 m_position;
		Vec3 m_scale;
		Vec3 m_rotation;
		float m_moveSpeed;
		int m_HP;
		int m_Rcrystal;
		int m_Bcrystal;
		//float m_count;//Respawn
		//float m_RespawnTime;
		//bool bRespawn;
		bool bMutekiFlg;
		float m_Mcount;
		float m_MTime;

		//void Respawn();
		void Move();
		Vec3 MoveVec();
		void Muteki();
		void ToGameOver();
		void ToClear();
	public:
		//HP
		void SetHP(int HP);
		int GetHP();
		//Crystal
		int GetCrystal();

		//Vec3 jumpVelocity;
		//private: bool bJump = false;
	public:
		Player(const std::shared_ptr<Stage>& stage,
			const wstring& line);

		void OnCreate() override;
		void OnUpdate() override;
		void OnCollisionEnter(std::shared_ptr<GameObject>& other) override;

	};
}
//end basecross

