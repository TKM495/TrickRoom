/*!
@file EnemyMove.h
@brief “G‚Ì“®‚«‚È‚Ç
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class EnemyMove : public GameObject {
		//float m_EnemySpeed;
		//float m_EnemyCount;
		//float m_Directions;
		//float m_MinusDirections;
		//float m_MoveTime;
		//float m_MoveTime2;
		//float m_MoveTime3;
		//float m_MoveTime4;

		// •`‰æÀ•W
		float m_PosX;
		float m_PosY;

		float m_Radius;// ”¼Œa(•`‰æ—p)

		// ’†SÀ•W
		float m_CenterX;
		float m_CenterY;

		float m_Angle;// Šp“x
		float m_Length;// ”¼Œa‚Ì’·‚³

		float m_RotationSpeed;

		float m_PI;
		float m_Deg;



	public:
		EnemyMove(const std::shared_ptr<Stage>& stage)
			: GameObject(stage),/* m_EnemySpeed(3), m_EnemyCount(0), m_Directions(1), m_MinusDirections(-1), m_MoveTime(2), m_MoveTime2(4), m_MoveTime3(6), m_MoveTime4(8),*/
				m_PosX(1), m_PosY(1), m_Radius(2), m_CenterX(-2), m_CenterY(-1), m_Angle(0), m_Length(2), m_RotationSpeed(5), m_PI(3.14), m_Deg(180.0)
		{

		}

		void OnCreate() override;
		void OnUpdate() override;

	};
}
