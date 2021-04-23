/*!
@file RouteMove.cpp
@brief ルートに沿った動きなど
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {
	void RouteMove::Excute()
	{
		auto stage = GetStage();

		auto transComp = GetGameObject()->GetComponent<Transform>();
		auto pos = transComp->GetPosition();

		auto ElapsedTime = App::GetApp()->GetElapsedTime();

		auto Move = m_moveDir[m_moveIndex] * m_Speed * ElapsedTime;
		pos += Move;
		transComp->SetPosition(pos);
	}

	void RouteMove::Hit()
	{
		switch (m_turnDir)
		{
		case TurnDir::Right:
			m_moveIndex++;
			if (Utility::GetArrayLength(m_moveDir) < m_moveIndex) {
				m_moveIndex = 0;
			}
			break;
		case TurnDir::Left:
			m_moveIndex--;
			if (m_moveIndex < 0) {
				m_moveIndex = Utility::GetArrayLength(m_moveDir);
			}
			break;
		default:
			//エラー
			break;
		}
	}
}
