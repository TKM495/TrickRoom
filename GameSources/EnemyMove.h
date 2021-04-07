/*!
@file EnemyMove.h
@brief “G‚Ì“®‚«‚È‚Ç
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class EnemyMove : public GameObject {
		float m_EnemySpeed;
		float m_EnemyCount;
		float m_Directions;
		float m_MinusDirections;
		float m_MoveTime;
		float m_MoveTime2;
		float m_MoveTime3;
		float m_MoveTime4;


	public:
		EnemyMove(const std::shared_ptr<Stage>& stage)
			: GameObject(stage), m_EnemySpeed(3), m_EnemyCount(0), m_Directions(1), m_MinusDirections(-1), m_MoveTime(2), m_MoveTime2(4), m_MoveTime3(6), m_MoveTime4(8)
		{

		}

		void OnCreate() override;
		void OnUpdate() override;

	};
}
