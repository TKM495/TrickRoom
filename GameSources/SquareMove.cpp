/*!
@file SquareMove.cpp
@brief ある点を中心とした四角形の上を移動する動きの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void SquareMove::OnCreate()
	{
		auto transComp = GetGameObject()->GetComponent<Transform>();
		auto pos = transComp->GetPosition();
		pos += Vec3(-m_length.x / 2.0f, 0.0f, m_length.y / 2.0f);
		transComp->SetPosition(pos);
	}

	void SquareMove::Excute()
	{
		auto transComp = GetGameObject()->GetComponent<Transform>();
		auto pos = transComp->GetPosition();

		const auto& app = App::GetApp();
		float ElapsedTime = app->GetElapsedTime();

		m_EnemyCount += 1 * ElapsedTime;

		if (m_EnemyCount < m_MoveTime)
		{

			auto Move = m_EnemySpeed * m_MinusDirections * ElapsedTime;
			pos += Vec3(Move, 0.0f, 0.0f);
			transComp->SetPosition(pos);

			//MessageBox(0, L"ミッション失敗です、やり直してください", L"Failed", 0);
		}

		if (m_MoveTime < m_EnemyCount && m_EnemyCount < m_MoveTime2)
		{

			auto Move = m_EnemySpeed * m_MinusDirections * ElapsedTime;
			pos += Vec3(0.0f, 0.0f, Move);
			transComp->SetPosition(pos);

			//MessageBox(0, L"ミッション失敗です、やり直してください", L"Failed", 0);

		}

		if (m_MoveTime2 < m_EnemyCount && m_EnemyCount < m_MoveTime3)
		{
			auto Move = m_EnemySpeed * m_Directions * ElapsedTime;
			pos += Vec3(Move, 0.0f, 0.0f);
			transComp->SetPosition(pos);

		}

		if (m_MoveTime3 < m_EnemyCount && m_EnemyCount < m_MoveTime4)
		{
			auto Move = m_EnemySpeed * m_Directions * ElapsedTime;
			pos += Vec3(0.0f, 0.0f, Move);
			transComp->SetPosition(pos);

		}

		if (m_MoveTime4 < m_EnemyCount)
		{
			m_EnemyCount = 0;
		}

	}
}