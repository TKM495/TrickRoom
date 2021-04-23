/*!
@file Player.h
@brief
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"

namespace basecross {
	class Player : public StageObject {

		shared_ptr<GameObject> m_model;
		Vec3 m_position;
		Vec3 m_scale;
		Vec3 m_rotation;
		Vec3 m_respawnPos;
		float m_moveSpeed;
		int m_Crystal;
		int m_HP;//HP(�����l�T)
		float m_count;//Respawn
		float m_RespawnTime;
		bool bRespawn;
		bool bDotFlg;
		float m_DotCount;
		float m_DotMaxCount;

		bool bMutekiFlg;
		float m_Mcount;
		float m_MTime;

		float rotationSpeed;

		float m_startPos;
		float m_dir;
		bool m_bExtrude;
		float m_deltaExtrude;
		//�_��
		int m_DrawCount;
		uint8_t m_BlinkMask;

		void Respawn();
		void Move();
		Vec3 MoveVec();
		void Muteki();
		void ToClear();
	public:
		//HP
		void SetHP(int HP);
		int GetHP();
		//Crystal
		int GetCrystal();

		void Draw();

		//Vec3 jumpVelocity;
		//private: bool bJump = false;
	public:
		Player(const std::shared_ptr<Stage>& stage,
			const wstring& line);

		void OnCreate() override;
		void OnUpdate() override;
		void OnCollisionEnter(std::shared_ptr<GameObject>& other) override;
		void OnCollisionExcute(std::shared_ptr<GameObject>& other) override;

	};
}
//end basecross

