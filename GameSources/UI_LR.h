/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class UI_LR :public GameObject {
		std::vector<VertexPositionColorTexture> vertices;
		float m_posX;
	public:
		UI_LR(const shared_ptr<Stage>& stage)
			:GameObject(stage),
			m_posX(0.0f)
		{}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}
//end basecross
