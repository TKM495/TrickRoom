/*!
@file Player.h
@brief
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"
#include "TimeCounter.h"

namespace basecross {
	class Player : public StageObject {
		//ステートマシーン
		unique_ptr< StateMachine<Player> >  m_StateMachine;
		wstringstream wss;
		shared_ptr<GameObject> m_model;
		TimeCounter m_timer;
		//Goal時の動き用
		float m_startToMiddleTime;
		float m_appealTime;
		float m_middleToEndTime;
		float m_moveTime;
		Vec3 m_startPos;
		Vec3 m_middlePos;
		Vec3 m_endPos;

		Vec3 m_position;
		Vec3 m_scale;
		Vec3 m_rotation;
		Vec3 m_respawnPos;
		float m_moveSpeed;
		Vec3 m_nowMoveSp;
		Vec3 m_nowPos;
		Vec3 m_beforePos;
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
		//プレイヤーモデルに通知するための変数
		bool m_bClear;
		float rotationSpeed;
		//落下判定
		bool m_bFalling;

		//トリックアート押し出し用
		float m_basePosY;
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
	public:
		//HP
		void SetHP(int HP);
		int GetHP();
		//Crystal
		int GetCrystal();
		bool GetbRespawn() {
			return bRespawn;
		}
		bool GetMutekiFlg() {
			return bMutekiFlg;
		}
		Vec3 GetNowMoveSp() {
			return m_nowMoveSp;
		}
		bool GetClearFlg() {
			return m_bClear;
		}
		Vec3 GetDiffPos() {
			auto diff = m_nowPos - m_beforePos;
			return diff;
		}
		void Draw();
		const unique_ptr<StateMachine<Player>>& GetStateMachine() {
			return m_StateMachine;
		}

		void StartInit();
		void DefaultInit();
		void DefaultBehavior();
		void GoalInit();
		void GoalBehavior();

		//Vec3 jumpVelocity;
		//private: bool bJump = false;
		Player(const std::shared_ptr<Stage>& stage,
			const wstring& line);

		void OnCreate() override;
		void OnUpdate() override;
		void OnCollisionEnter(std::shared_ptr<GameObject>& other) override;
		void OnCollisionExcute(std::shared_ptr<GameObject>& other) override;
	};

	//エラー防止のため、実際に動かせるようになるまでは
	//ここで重力やコリジョンを停止させる
	class PlayerStartState : public ObjState<Player> {
		PlayerStartState() {}
	public:
		static shared_ptr<PlayerStartState> Instance();
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};

	class PlayerDefaultState : public ObjState<Player> {
		PlayerDefaultState() {}
	public:
		static shared_ptr<PlayerDefaultState> Instance();
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};

	class PlayerGoalState : public ObjState<Player> {
		PlayerGoalState() {}
	public:
		static shared_ptr<PlayerGoalState> Instance();
		virtual void Enter(const shared_ptr<Player>& Obj)override;
		virtual void Execute(const shared_ptr<Player>& Obj)override;
		virtual void Exit(const shared_ptr<Player>& Obj)override;
	};
}
//end basecross

