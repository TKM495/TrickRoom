/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void CircularMove::OnCreate() {
		auto transComp = GetGameObject()->GetComponent<Transform>();
		auto pos = transComp->GetPosition();
		m_CenterX = pos.x;
		m_CenterY = pos.y;
	}

	void CircularMove::Excure() {
		auto transComp = GetGameObject()->GetComponent<Transform>();
		auto pos = transComp->GetPosition();

		const auto& app = App::GetApp();
		float ElapsedTime = app->GetElapsedTime();


		float radius = m_Angle * m_PI / m_Deg;
		auto add_x = cos(radius) * m_Length;
		auto add_y = sin(radius) * m_Length;

		m_PosX = m_CenterX + add_x;
		m_PosY = m_CenterY + add_y;

		m_Angle += m_RotationSpeed * ElapsedTime;

		transComp->SetPosition(m_PosX, m_Radius, m_PosY);
	}
}
//end basecross
