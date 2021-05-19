#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TitleCamera::OnCreate()
	{
		auto eye = Vec3(cosf(m_angleRadX), 0.0f, sinf(m_angleRadX)) * length;
		//eye.y = 7.0f;

		SetEye(eye + m_baseEye);
		//SetAt(GetAt());
	}

	void TitleCamera::OnUpdate()
	{
		auto& app = App::GetApp();
		//auto scene = app->GetScene<Scene>();
		//auto stage = scene->GetActiveStage();
		//auto gameObjects = stage->GetGameObjectVec();

		//std::shared_ptr<CameraBlock> block;
		//for (auto gameObject : gameObjects)
		//{
		//	block = dynamic_pointer_cast<CameraBlock>(gameObject);
		//	if (block)
		//	{
		//		break;
		//	}
		//}

		auto device = app->GetInputDevice();
		const auto& pad = device.GetControlerVec()[0];

		float h = pad.fThumbRX;
		float v = pad.fThumbRY;
		float stickRad = atan2f(v, h); // スティックの傾きをラジアン角に変換

		auto delta = app->GetElapsedTime();
		//auto at = block->GetComponent<Transform>()->GetPosition();
		//SetAt(at);

		if (h != 0 && v != 0)
		{
			m_angleRadX += XMConvertToRadians(m_Center) * h * delta;
			m_angleRadY += XMConvertToRadians(m_Center) * v * delta;

			if (m_angleRadX < XMConvertToRadians(m_XMax))
			{
				m_angleRadX = XMConvertToRadians(m_XMax);
			}

			if (m_angleRadX > XMConvertToRadians(m_XMin))
			{
				m_angleRadX = XMConvertToRadians(m_XMin);
			}

			if (m_angleRadY < XMConvertToRadians(m_YMax))
			{
				m_angleRadY = XMConvertToRadians(m_YMax);
			}

			if (m_angleRadY > XMConvertToRadians(m_YMin))
			{
				m_angleRadY = XMConvertToRadians(m_YMin);
			}

			auto eye = Vec3(cosf(m_angleRadX), cosf(m_angleRadY), sinf(m_angleRadX)) * length;
			m_eye = GetAt() + eye + m_baseEye;
		}

		else
		{
			m_angleRadX = XMConvertToRadians(-m_Center);
			m_angleRadY = XMConvertToRadians(-m_Center);
			auto eye = Vec3(cosf(m_angleRadX), 0.0f, sinf(m_angleRadX)) * length;
			//eye.y = 7.0f;
			m_eye = eye + m_baseEye;
			//SetAt(0.0f, 1.0f, 0.0f);

		}
		auto eye = Lerp::CalculateLerp(GetEye(), m_eye, 0.0f, 1.0f, 0.15f, Lerp::rate::Linear);
		SetEye(eye);
		//カメラの移動制限が必要
	}
}