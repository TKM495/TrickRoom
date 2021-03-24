/*!
@file MainCamera.cpp
@brief ���C���J�����Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	MainCamera::MainCamera()
		:m_offset(10.0f, 10.0f, -10.0f), m_Angle(-10.0f, 10.0f, -10.0f), bSetPers(false), SetWidth(20.0f), SetHeight(12.5f), m_CameraState(state::Right)
	{

	}

	void MainCamera::OnCreate()
	{
		SetPers(false);
		Camera::SetWidth(SetWidth);
		Camera::SetHeight(SetHeight);
	}

	void MainCamera::OnUpdate()
	{
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

		SetAt(at);

		if (pad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)//RB
		{
			m_CameraState = state::Right;
		}

		if (pad.wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)//LB
		{
			m_CameraState = state::Left;
		}

		switch (m_CameraState)
		{
		case state::Right:
			SetEye(at + m_offset);
			break;
		case state::Left:
			SetEye(at + m_Angle);
			break;
		default:
			break;
		}

	}

	Vec3 MainCamera::GetAngle()
	{
		return m_Angle;
	}

}
