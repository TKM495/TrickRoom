#pragma once
#include "stdafx.h"
#include "Player.h"
#include "TimeCounter.h"

namespace basecross {
	class PlayerModel :public GameObject {
		//ステートマシーン
		unique_ptr< StateMachine<PlayerModel> >  m_StateMachine;

		shared_ptr<Player> m_player;
		TimeCounter m_timer;
	public:
		PlayerModel(const shared_ptr<Stage>& stage,
			const shared_ptr<Player> player)
			:GameObject(stage),
			m_player(player)
		{}

		void OnCreate()override;
		void OnUpdate()override;

		void RunInit();
		void RunBehavior();
		void DamageInit();
		void DamageBehavior();
		void NormalInit();
		void NormalBehavior();
		void GoalInit();
		void GoalBehavior();

		const unique_ptr<StateMachine<PlayerModel>>& GetStateMachine() {
			return m_StateMachine;
		}
		void Motion(float delta);
	};

	class PlayerModelRun : public ObjState<PlayerModel> {
		PlayerModelRun() {}
	public:
		static shared_ptr<PlayerModelRun> Instance();
		virtual void Enter(const shared_ptr<PlayerModel>& Obj)override;
		virtual void Execute(const shared_ptr<PlayerModel>& Obj)override;
		virtual void Exit(const shared_ptr<PlayerModel>& Obj)override;
	};
	class PlayerModelDamage : public ObjState<PlayerModel> {
		PlayerModelDamage() {}
	public:
		static shared_ptr<PlayerModelDamage> Instance();
		virtual void Enter(const shared_ptr<PlayerModel>& Obj)override;
		virtual void Execute(const shared_ptr<PlayerModel>& Obj)override;
		virtual void Exit(const shared_ptr<PlayerModel>& Obj)override;
	};
	class PlayerModelNormal : public ObjState<PlayerModel> {
		PlayerModelNormal()
			:m_motionOffset(0.2f)
		{}
		float m_motionOffset;
		TimeCounter m_timer;
	public:
		static shared_ptr<PlayerModelNormal> Instance();
		virtual void Enter(const shared_ptr<PlayerModel>& Obj)override;
		virtual void Execute(const shared_ptr<PlayerModel>& Obj)override;
		virtual void Exit(const shared_ptr<PlayerModel>& Obj)override;
	};
	class PlayerModelGoal : public ObjState<PlayerModel> {
		PlayerModelGoal() {}
	public:
		static shared_ptr<PlayerModelGoal> Instance();
		virtual void Enter(const shared_ptr<PlayerModel>& Obj)override;
		virtual void Execute(const shared_ptr<PlayerModel>& Obj)override;
		virtual void Exit(const shared_ptr<PlayerModel>& Obj)override;
	};
}