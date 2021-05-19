/*!
@file RouteMove.cpp
@brief ���[�g�ɉ����������Ȃ�
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {
	void RouteMove::OnCreate() {
		auto transComp = GetGameObject()->GetComponent<Transform>();
		m_defPos = transComp->GetPosition();
	}

	void RouteMove::Excute()
	{
		if (m_bHit) {
			//�Փ˔����̈ʒu���擾���邽�߂����Ŏ��s
			auto transComp = GetGameObject()->GetComponent<Transform>();
			m_defPos = transComp->GetPosition();
			m_bHit = false;
		}
		auto stage = GetStage();

		auto transComp = GetGameObject()->GetComponent<Transform>();
		auto pos = transComp->GetPosition();

		auto ElapsedTime = App::GetApp()->GetElapsedTime();

		auto Move = m_moveDir[m_moveIndex] * m_Speed * ElapsedTime;
		pos += Move;
		switch (m_limitAxis[m_moveIndex])
		{
		case LimitAxis::X:
			pos.x = m_defPos.x;
			break;
		case LimitAxis::Z:
			pos.z = m_defPos.z;
			break;
		}
		pos.y = m_defPos.y;
		transComp->SetPosition(pos);
	}

	void RouteMove::Hit()
	{
		m_bHit = true;
		switch (m_turnDir)
		{
		case TurnDir::Left:
			m_moveIndex++;
			if (Utility::GetArrayLength(m_moveDir) < m_moveIndex) {
				m_moveIndex = 0;
			}
			break;
		case TurnDir::Right:
			m_moveIndex--;
			if (m_moveIndex < 0) {
				m_moveIndex = Utility::GetArrayLength(m_moveDir);
			}
			break;
		default:
			//�G���[
			break;
		}
	}
}
