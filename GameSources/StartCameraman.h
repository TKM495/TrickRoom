#pragma once
#include "stdafx.h"
#include "StageObject.h"

namespace basecross {
	class StartCameraman :public GameObject {
		Vec3 m_StartPos;
		Vec3 m_EndPos;
		Vec3 m_AtStartPos;
		Vec3 m_AtEndPos;
		Vec3 m_AtPos;
		float m_TotalTime;
		//ステートマシーン
		unique_ptr< StateMachine<StartCameraman> >  m_StateMachine;
	public:
	public:
		StartCameraman(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}
		void OnCreate() override;
		void OnUpdate() override;

		const unique_ptr<StateMachine<StartCameraman>>& GetStateMachine() {
			return m_StateMachine;
		}

		Vec3 GetAtPos() const {
			return m_AtPos;
		}
		void ToGoalEnterBehavior();
		void ToStartEnterBehavior();
		bool ExcuteBehavior(float totaltime);
		void EndStateEnterBehavior();
	};

	class StartCameramanToGoalState : public ObjState<StartCameraman>
	{
		StartCameramanToGoalState() {}
	public:
		static shared_ptr<StartCameramanToGoalState> Instance();
		virtual void Enter(const shared_ptr<StartCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<StartCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<StartCameraman>& Obj)override;
	};

	class StartCameramanToStartState : public ObjState<StartCameraman>
	{
		StartCameramanToStartState() {}
	public:
		static shared_ptr<StartCameramanToStartState> Instance();
		virtual void Enter(const shared_ptr<StartCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<StartCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<StartCameraman>& Obj)override;
	};

	class StartCameramanEndState : public ObjState<StartCameraman>
	{
		StartCameramanEndState() {}
	public:
		static shared_ptr<StartCameramanEndState> Instance();
		virtual void Enter(const shared_ptr<StartCameraman>& Obj)override;
		virtual void Execute(const shared_ptr<StartCameraman>& Obj)override;
		virtual void Exit(const shared_ptr<StartCameraman>& Obj)override;
	};
}
//end basecross