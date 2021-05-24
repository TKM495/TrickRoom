/*!
@file MainCamera.cpp
@brief
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	MainCamera::MainCamera()
		:m_offset(10.0f, 10.0f, -10.0f), m_Angle(-10.0f, 10.0f, -10.0f), bSetPers(false), SetWidth(18.0f), SetHeight(0.0f), m_CameraState(state::Right),
		bLeapFlg(false), m_LeapTime(0), m_LeapSpeed(1), m_LeapOffset(m_offset), m_CameraCount(0),
		m_goalPosForward(Vec3(0.0f), Vec3(0.0f)), m_bClear(false)
	{
		isFirst = true;
	}

	void MainCamera::OnCreate()
	{
		//ステートマシンの構築
		m_StateMachine.reset(new StateMachine<MainCamera>(GetThis<MainCamera>()));
		//初期ステートの設定
		m_StateMachine->ChangeState(MainCameraInitState::Instance());
	}

	void MainCamera::OnUpdate()
	{
		m_StateMachine->Update();
	}

	void MainCamera::StartInit() {
		auto scene = App::GetApp()->GetScene<Scene>();
		auto stage = scene->GetActiveTypeStage<GameStage>();

		auto player = stage->GetSharedGameObject<Player>(L"Player");
		auto playerPos = player->GetComponent<Transform>()->GetPosition();

		SetPers(false);
		Camera::SetWidth(SetWidth);
		SetHeight = SetWidth * 0.625f;
		Camera::SetHeight(SetHeight);

		m_endAt = playerPos;
		auto startAt = m_goalPosForward.origin;
		startAt.y = m_endAt.y;
		m_startAt = startAt;

		SetAt(m_goalPosForward.origin);
		SetEye(GetAt() + m_offset);
		//念のため初期化
		m_timer.Reset();
		m_timer.SetCountTime(3.0f);
	}

	void MainCamera::StartBehavior() {
		Easing<Vec3> easing;
		auto at = easing.EaseInOut(EasingType::Cubic, m_startAt, m_endAt, m_timer.GetTime(), m_timer.GetCountTime());
		SetAt(at);
		SetEye(GetAt() + m_offset);
		if (m_timer.Count()) {
			m_StateMachine->ChangeState(MainCameraDefaultState::Instance());
		}
	}

	void MainCamera::DefaultInit() {
		SetPers(false);
		Camera::SetWidth(SetWidth);
		SetHeight = SetWidth * 0.625f;
		Camera::SetHeight(SetHeight);
	}

	void MainCamera::DefaultBehavior() {
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();
		auto device = app->GetInputDevice();
		const auto& pad = device.GetControlerVec()[0];

		auto scene = app->GetScene<Scene>();
		auto stage = scene->GetActiveStage();
		auto gameObjects = stage->GetGameObjectVec();
		std::shared_ptr<Player> player;

		for (auto gameObject : gameObjects)
		{
			player = dynamic_pointer_cast<Player>(gameObject);
			if (player)
			{
				break;
			}
		}

		//カメラ処理
		auto TransComp = player->GetComponent<Transform>();
		auto at = TransComp->GetPosition();
		auto gameStage = dynamic_pointer_cast<GameStage>(stage);
		auto limit = gameStage->GetGoalX();
		if (at.x < limit) {
			at.x = limit;
		}

		SetAt(at);

		if (isFirst)
		{
			SetEye(at + m_offset);
			isFirst = false;
		}

		switch (gameStage->GetState())
		{
		case GameStage::GameState::PLAYING:
			break;
		case GameStage::GameState::CLEAR:
			m_bClear = true;
			break;
		default:
			switch (m_CameraState)
			{
			case basecross::state::Right:
				SetEye(at + m_offset);
				break;
			case basecross::state::Left:
				SetEye(at + m_Angle);
				break;
			}
			return;
			break;
		}

		if (!bLeapFlg)
		{
			SetEye(at + m_LeapOffset);
			if (pad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
			{
				if (m_CameraState != state::Right)//RB
				{
					m_CameraState = state::Right;
					bLeapFlg = true;
					m_Eye = GetEye();
					m_LeapOffset = m_offset;

					m_CameraCount++;

					//SetEye(at + m_offset);
				}
				else {
					auto audio = App::GetApp()->GetXAudio2Manager();
					audio->Start(L"IncorrectSE", 0, 0.1f);
				}
			}

			if (pad.wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
			{
				if (m_CameraState != state::Left)//LB
				{
					m_CameraState = state::Left;
					bLeapFlg = true;
					m_Eye = GetEye();
					m_LeapOffset = m_Angle;

					m_CameraCount++;

					//SetEye(at + m_Angle);
				}
				else {
					auto audio = App::GetApp()->GetXAudio2Manager();
					audio->Start(L"IncorrectSE", 0, 0.1f);
				}
			}
		}

		else
		{
			auto& app = App::GetApp();
			float delta = app->GetElapsedTime();

			m_LeapTime += m_LeapSpeed * delta;

			Vec3 LeapEye = MyMath::Leap(m_Eye, Vec3(at + m_LeapOffset), m_LeapTime);
			SetEye(LeapEye);

			if (m_LeapTime >= 1)
			{
				bLeapFlg = false;
				m_LeapTime = 0;
			}
		}

		//途中の処理の影響を避けるために最後においている
		if (m_bClear) {
			m_StateMachine->ChangeState(MainCameraGoalState::Instance());
		}
	}

	void MainCamera::GoalInit() {
		SetPers(true);
		auto goalPos = m_goalPosForward.origin;
		goalPos.y += 1.0f;
		auto goalForward = m_goalPosForward.dir;
		SetAt(goalPos);
		auto eye = goalPos + (goalForward * 6.0f);
		SetEye(eye);
	}

	void MainCamera::GoalBehavior() {
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveTypeStage<GameStage>();
		if (stage->GetState() == GameStage::GameState::FADEOUT) {
			Zoom(0.2f);
		}
	}

	Vec3 MainCamera::GetAngle()
	{
		return m_Angle;
	}

	bool MainCamera::GetbLeapFlg()
	{
		return bLeapFlg;
	}

	void MainCamera::Zoom(float speed) {
		if (IsPers()) {
			SetFovY(GetFovY() - (speed * 0.05f));
		}
		else {
			SetWidth -= speed;
			Camera::SetWidth(SetWidth);
			SetHeight = SetWidth * 0.625f;
			Camera::SetHeight(SetHeight);
		}
	}
	int MainCamera::GetCameraCount()
	{
		return m_CameraCount;
	}

	shared_ptr<MainCameraInitState> MainCameraInitState::Instance() {
		static shared_ptr<MainCameraInitState> instance(new MainCameraInitState);
		return instance;
	}
	void MainCameraInitState::Enter(const shared_ptr<MainCamera>& Obj) {}
	void MainCameraInitState::Execute(const shared_ptr<MainCamera>& Obj) {
		if (Obj->GetGoalPosForward().origin != Vec3(0.0f)) {
			Obj->GetStateMachine()->ChangeState(MainCameraStartState::Instance());
		}
	}
	void MainCameraInitState::Exit(const shared_ptr<MainCamera>& Obj) {}


	shared_ptr<MainCameraStartState> MainCameraStartState::Instance() {
		static shared_ptr<MainCameraStartState> instance(new MainCameraStartState);
		return instance;
	}
	void MainCameraStartState::Enter(const shared_ptr<MainCamera>& Obj) {
		Obj->StartInit();
	}
	void MainCameraStartState::Execute(const shared_ptr<MainCamera>& Obj) {
		Obj->StartBehavior();
	}
	void MainCameraStartState::Exit(const shared_ptr<MainCamera>& Obj) {}


	shared_ptr<MainCameraDefaultState> MainCameraDefaultState::Instance() {
		static shared_ptr<MainCameraDefaultState> instance(new MainCameraDefaultState);
		return instance;
	}
	void MainCameraDefaultState::Enter(const shared_ptr<MainCamera>& Obj) {
		Obj->DefaultInit();
	}
	void MainCameraDefaultState::Execute(const shared_ptr<MainCamera>& Obj) {
		Obj->DefaultBehavior();
	}
	void MainCameraDefaultState::Exit(const shared_ptr<MainCamera>& Obj) {}


	shared_ptr<MainCameraGoalState> MainCameraGoalState::Instance() {
		static shared_ptr<MainCameraGoalState> instance(new MainCameraGoalState);
		return instance;
	}
	void MainCameraGoalState::Enter(const shared_ptr<MainCamera>& Obj) {
		Obj->GoalInit();
	}
	void MainCameraGoalState::Execute(const shared_ptr<MainCamera>& Obj) {
		Obj->GoalBehavior();
	}
	void MainCameraGoalState::Exit(const shared_ptr<MainCamera>& Obj) {}
}
