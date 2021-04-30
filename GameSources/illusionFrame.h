/*!
@file illusionFrame.h
@brief çˆéãÉtÉåÅ[ÉÄ
*/

#pragma once
#include "stdafx.h"
#include "LineSprite.h"

namespace basecross {
	class illusionFrame :public GameObject {
		vector<shared_ptr<LineSprite>> m_baseSprites;
		vector<shared_ptr<LineSprite>> m_arrowSprites;
		float m_boxLength;
		float m_boxHeight;
		float m_arrowFeathersAngle;
		float m_arrowFeathersLength;
		float m_lineThickness;
		bool m_bItemActive;
	public:
		illusionFrame(const shared_ptr<Stage>& stage,
			float boxLength,
			float boxHeight,
			float thickness = 5.0f)
			:GameObject(stage), m_boxLength(boxLength), m_boxHeight(boxHeight),
			m_lineThickness(thickness),
			m_bItemActive(false)
		{}

		void OnCreate()override;
		void SetPosition(Vec2 pos);
		void SetDrawActive(bool flg);
		void SetItemActive(bool flg);
	};
}
//end basecross