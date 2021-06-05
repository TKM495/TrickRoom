/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class CircularMove :public Behavior {
		// �`����W
		float m_PosX;
		float m_PosY;

		float m_Radius;// ���a(�`��p)

		// ���S���W
		float m_CenterX;
		float m_CenterY;

		float m_Angle;// �p�x
		float m_Length;// ���a�̒���

		float m_RotationSpeed;

		float m_PI;
		float m_Deg;
	public:
		CircularMove(const shared_ptr<GameObject>& obj)
			:Behavior(obj), m_PosX(1), m_PosY(1), m_Radius(2),
			m_CenterX(0), m_CenterY(0),
			m_Angle(0), m_Length(2), m_RotationSpeed(5),
			m_PI(3.14), m_Deg(180.0)
		{}

		void OnCreate()override;
		void Excute();

		void SetSpeed(float Speed)
		{
			m_RotationSpeed = Speed;
		}
		void SetRadius(float radius) {
			m_Radius = radius;
		}
		void SetOffset(float offset) {
			m_Angle = offset;
		}
		float GetSpeed()
		{
			return m_RotationSpeed;
		}

		void SetLength(float Length)
		{
			m_Length = Length;
		}

		float GetLength()
		{
			return m_Length;
		}
	};
}
//end basecross
