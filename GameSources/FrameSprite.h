/*!
@file FrameSprite.h
@brief �w�i�摜
*/

#pragma once
#include "stdafx.h"
#include "StringSprite2.h"

namespace basecross {
	class FrameSprite :public GameObject {
		//���Ԍv���p
		float m_delta;
		//��A�N�e�B�u�ɂȂ�܂ł̎���
		float m_deActiveTime;
		//��A�N�e�B�u���ǂ���
		bool m_bDeactive;

		Vec2 m_position;
		Vec2 m_size;
		Col4 m_color;
		Align::Horizontal m_horizontal;
		Align::Vertical m_vertical;
		vector<VertexPositionColorTexture> vertices;
		void UpdateVertices();
	public:
		FrameSprite(const shared_ptr<Stage>& stage,
			const Vec2& size)
			:GameObject(stage),
			m_size(size),
			m_color(Col4(1.0f)),
			m_horizontal(Align::Horizontal::Center),
			m_vertical(Align::Vertical::Center)
		{}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void SetSize(Vec2 size);
		void SetSize(float size);
		void SetPosition(Vec2 pos);
		void SetColor(Col4 color);

		shared_ptr<FadeComponent> GetFadeComp() {
			return GetComponent<FadeComponent>();
		}

		void Deactive(float time) {
			m_deActiveTime = time;
			SetUpdateActive(true);
		}
		void Deactive() {
			Deactive(0.0f);
		}
	};
}
//end basecross
