/*!
@file FrameSprite.h
@brief ”wŒi‰æ‘œ
*/

#pragma once
#include "stdafx.h"
#include "StringSprite2.h"

namespace basecross {
	class FrameSprite :public GameObject {
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
		void SetSize(Vec2 size);
		void SetSize(float size);
		void SetPosition(Vec2 pos);
		void SetColor(Col4 color);
	};
}
//end basecross
