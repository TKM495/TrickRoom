/*!
@file Dot1x1.h
@brief 1x1‚Ìƒhƒbƒg
*/

#pragma once
#include "stdafx.h"
#include "StringSprite2.h"

namespace basecross {
	struct Dot1x1Data {
		Vec2 position;
		Vec2 size;
		Col4 color;
		Align::Horizontal horizontal;
		Align::Vertical vertical;
	};

	class Dot1x1 :public GameObject {
		Dot1x1Data m_data;
		vector<VertexPositionColorTexture> vertices;
	public:
		Dot1x1(const shared_ptr<Stage>& stage,
			Dot1x1Data data)
			:GameObject(stage),
			m_data(data)
		{}

		void OnCreate()override;

		void SetAlignHorizontal(Align::Horizontal hor);
		void SetAlignVertical(Align::Vertical ver);

		void SetSize(Vec2 size);

	};
}
//end basecross
