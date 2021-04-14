/*!
@file MainCamera.cpp
@brief ���C���J�����Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	MainCamera::MainCamera()
		:m_offset(10.0f, 10.0f, -10.0f), m_Angle(-10.0f, 10.0f, -10.0f), bSetPers(false), SetWidth(20.0f), SetHeight(12.5f), m_CameraState(state::Right),
		bLeapFlg(false), m_LeapTime(0), m_LeapSpeed(1), m_LeapOffset(m_offset),m_CameraOffset(-5.0f,0.0f,0.0f)
	{
		isFirst = true;
	}

	void MainCamera::OnCreate()
	{

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
		auto at = TransComp->GetPosition() + m_CameraOffset;

		SetAt(at);

		if (isFirst)
		{
			SetEye(at + m_offset);
			isFirst = false;
		}

		if (!bLeapFlg)
		{
			SetEye(at + m_LeapOffset);
			if (pad.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER && m_CameraState != state::Right)//RB
			{
				m_CameraState = state::Right;
				bLeapFlg = true;
				m_Eye = GetEye();
				m_LeapOffset = m_offset;

				//SetEye(at + m_offset);
			}

			if (pad.wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER && m_CameraState != state::Left)//LB
			{
				m_CameraState = state::Left;
				bLeapFlg = true;
				m_Eye = GetEye();
				m_LeapOffset = m_Angle;

				//SetEye(at + m_Angle);
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
	}

	Vec3 MainCamera::GetAngle()
	{
		return m_Angle;
	}

	bool MainCamera::GetbLeapFlg()
	{
		return bLeapFlg;
	}
}
