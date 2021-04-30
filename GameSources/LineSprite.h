/*!
@file LineSprite.h
@brief ���C���X�v���C�g
*/

#pragma once
#include "stdafx.h"
#include "StringSprite2.h"

namespace basecross {
	struct LineSpriteParam {
		float Length;
		float Thickness;
		Col4 Color;
		Align::Horizontal Horizontal;
		Vec2 Position;
		float Rotation;
	};

	class LineSprite :public GameObject {
		//���̐F
		Col4 m_color;
		//���̒���
		float m_length;
		//���̑���
		float m_thickness;
		//���S�ʒu
		Align::Horizontal m_horizontal;
	public:
		LineSprite(const shared_ptr<Stage>& stage,
			Align::Horizontal horizontal = Align::Horizontal::Left)
			:GameObject(stage), m_color(Col4(1.0f)),
			m_length(50.0f), m_thickness(10.0f), m_horizontal(horizontal)
		{}

		void OnCreate()override;

		void SetPosition(Vec2 pos);
		void SetRotation(float rot);
		void SetLength(float length);
		void SetThickness(float thickness);
		void SetStatus(float length, float thickness, Col4 color);
		void SetStatus(float length, float thickness);
		void SetColor(Col4 color);

		Vec2 GetPosition();
		float GetRotation();
		float GetLength();
		float GetThickness();
		Col4 GetColor();
	};
}
//end basecross