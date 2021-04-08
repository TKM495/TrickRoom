/*!
@file SquareMove.h
@brief ある点を中心とした四角形の上を移動する動き
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SquareMove : public Behavior {
		float m_EnemySpeed;
		float m_EnemyCount;
		float m_Directions;
		float m_MinusDirections;
		float m_MoveTime;
		float m_MoveTime2;
		float m_MoveTime3;
		float m_MoveTime4;

		Vec2 m_length;
	public:
		SquareMove(const std::shared_ptr<GameObject>& obj)
			: Behavior(obj), m_EnemySpeed(3), m_EnemyCount(0),
			m_Directions(1), m_MinusDirections(-1), m_MoveTime(2),
			m_MoveTime2(4), m_MoveTime3(6), m_MoveTime4(8),
			m_length(Vec2(2.0f * m_EnemySpeed))
		{

		}

		void OnCreate() override;
		void SetSpeed(float speed) {
			m_EnemySpeed = speed;
		}
		void SetLength(Vec2 length) {
			m_length = length;
			auto baseX = m_length.x / m_EnemySpeed;
			auto baseY = m_length.y / m_EnemySpeed;
			m_MoveTime = baseX;
			m_MoveTime2 = m_MoveTime + baseY;
			m_MoveTime3 = m_MoveTime2 + baseX;
			m_MoveTime4 = m_MoveTime3 + baseY;
		}
		void Excute();

	};
}
