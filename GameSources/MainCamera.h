/*!
@file MainCamera.h
@brief
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"
#include "TimeCounter.h"

namespace basecross {
	enum class state
	{
		Right,
		Left,
		moveflg
	};

	class MainCamera :public Camera
	{
		//ステートマシーン
		unique_ptr< StateMachine<MainCamera> >  m_StateMachine;
		ObjectPositionForward m_goalPosForward;
		TimeCounter m_timer;
		Vec3 m_startAt;
		Vec3 m_endAt;

		Vec3 m_offset;
		Vec3 m_Angle;
		bool bSetPers;
		float SetWidth;
		float SetHeight;
		Vec3 GetAngle();
		bool bLeapFlg;
		float m_LeapTime;
		float m_LeapSpeed;
		Vec3 m_Eye;
		Vec3 m_LeapOffset;

		state m_CameraState;

		bool isFirst;
		void Zoom(float speed);
		bool m_bClear;
		int m_CameraCount;

	public:
		MainCamera();

		void OnCreate() override;
		void OnUpdate() override;
		state GetCamState() {
			return m_CameraState;
		}
		bool GetbLeapFlg();
		int GetCameraCount();

		void StartBehavior();
		void StartInit();
		void DefaultBehavior();
		void DefaultInit();
		void GoalBehavior();
		void GoalInit();
		void SetGoalPosForward(ObjectPositionForward opf) {
			m_goalPosForward = opf;
		}
		ObjectPositionForward GetGoalPosForward() {
			return m_goalPosForward;
		}

		const unique_ptr<StateMachine<MainCamera>>& GetStateMachine() {
			return m_StateMachine;
		}

	};

	//ゴールの情報が入ってくるまでここで処理を止める
	class MainCameraInitState : public ObjState<MainCamera> {
		MainCameraInitState() {}
	public:
		static shared_ptr<MainCameraInitState> Instance();
		virtual void Enter(const shared_ptr<MainCamera>& Obj)override;
		virtual void Execute(const shared_ptr<MainCamera>& Obj)override;
		virtual void Exit(const shared_ptr<MainCamera>& Obj)override;
	};

	class MainCameraStartState : public ObjState<MainCamera> {
		MainCameraStartState() {}
	public:
		static shared_ptr<MainCameraStartState> Instance();
		virtual void Enter(const shared_ptr<MainCamera>& Obj)override;
		virtual void Execute(const shared_ptr<MainCamera>& Obj)override;
		virtual void Exit(const shared_ptr<MainCamera>& Obj)override;
	};

	class MainCameraDefaultState : public ObjState<MainCamera> {
		MainCameraDefaultState() {}
	public:
		static shared_ptr<MainCameraDefaultState> Instance();
		virtual void Enter(const shared_ptr<MainCamera>& Obj)override;
		virtual void Execute(const shared_ptr<MainCamera>& Obj)override;
		virtual void Exit(const shared_ptr<MainCamera>& Obj)override;
	};

	class MainCameraGoalState : public ObjState<MainCamera> {
		MainCameraGoalState() {}
	public:
		static shared_ptr<MainCameraGoalState> Instance();
		virtual void Enter(const shared_ptr<MainCamera>& Obj)override;
		virtual void Execute(const shared_ptr<MainCamera>& Obj)override;
		virtual void Exit(const shared_ptr<MainCamera>& Obj)override;
	};
}
