#pragma once
#include "stdafx.h"
#include "StageObject.h"

namespace basecross {
	class GoalModel : public GameObject
	{
		unique_ptr<StateMachine<GoalModel>> m_stateMachine;
		ObjectParam m_param;
		bool m_bOpen;
		bool m_bOnce;
	public :
		GoalModel(const std::shared_ptr<Stage>& stage,
			ObjectParam param);

		void OnCreate() override;
		void OnUpdate() override;

		void OpenBehavior();
		const unique_ptr<StateMachine<GoalModel>>& GetStateMachine() {
			return m_stateMachine;
		}
	};

	class GoalModelOpen :public ObjState<GoalModel> {
		GoalModelOpen() {}
	public:
		static shared_ptr<GoalModelOpen> Instance();
		virtual void Enter(const shared_ptr<GoalModel>& Obj)override;
		virtual void Execute(const shared_ptr<GoalModel>& Obj)override;
		virtual void Exit(const shared_ptr<GoalModel>& Obj)override;
	};
	class GoalModelStay :public ObjState<GoalModel> {
		GoalModelStay() {}
	public:
		static shared_ptr<GoalModelStay> Instance();
		virtual void Enter(const shared_ptr<GoalModel>& Obj)override;
		virtual void Execute(const shared_ptr<GoalModel>& Obj)override;
		virtual void Exit(const shared_ptr<GoalModel>& Obj)override;
	};
}
