/*!
@file SinCurve.cpp
@brief サインカーブ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void SinCurve::OnCreate() {
		auto ptrTrans = GetGameObject()->GetComponent<Transform>();
		m_Position = ptrTrans->GetPosition();
	}

	void SinCurve::Excute(float cycle, float speed) {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += elapsedTime;
		if (m_TotalTime >= XM_2PI)
		{
			m_TotalTime = 0.0f;
		}

		auto ptrTrans = GetGameObject()->GetComponent<Transform>();
		float posZ = sin(m_TotalTime * cycle + m_offset) * speed + m_Position.z;
		auto pos = ptrTrans->GetPosition();
		pos.z = posZ;
		ptrTrans->SetPosition(pos);
	}

}
//end basecross
