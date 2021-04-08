/*!
@file EnemyMove.cpp
@brief “G‚Ì“®‚«
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void EnemyMove::OnCreate()
	{
		auto drawComp = AddComponent<BcPNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(-9.0f, 0.0f, 3.0f);

	}

	void EnemyMove::OnUpdate()
	{
		CircleMove();
	}

	void EnemyMove::CircleMove()
	{
		auto stage = GetStage();

		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();

		const auto& app = App::GetApp();
		float ElapsedTime = app->GetElapsedTime();


		float radius = m_Angle * m_PI / m_Deg;
		auto add_x = cos(radius) * m_Length;
		auto add_y = sin(radius) * m_Length;

		m_PosX = m_CenterX + add_x;
		m_PosY = m_CenterY + add_y;

		m_Angle += m_RotationSpeed;

		transComp->SetPosition(m_PosX, m_Radius, m_PosY);
	}

	void EnemyMove::SquareMove()
	{
		auto stage = GetStage();

		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();

		const auto& app = App::GetApp();
		float ElapsedTime = app->GetElapsedTime();

		m_EnemyCount += 1 * ElapsedTime;

		if (m_EnemyCount < m_MoveTime)
		{

			auto Move = m_EnemySpeed * m_MinusDirections * ElapsedTime;
			pos += Vec3(Move, 0.0f, 0.0f);
			transComp->SetPosition(pos);
		}

		if (m_MoveTime < m_EnemyCount && m_EnemyCount < m_MoveTime2)
		{

			auto Move = m_EnemySpeed * m_MinusDirections * ElapsedTime;
			pos += Vec3(0.0f, 0.0f, Move);
			transComp->SetPosition(pos);
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

	void EnemyMove::SetSpeed(int Speed)
	{
		m_RotationSpeed = Speed;
	}

	int EnemyMove::GetSpeed()
	{
		return m_RotationSpeed;
	}

	void EnemyMove::SetLength(float Length)
	{
		m_Length = Length;
	}

	float EnemyMove::GetLength()
	{
		return m_Length;
	}
}