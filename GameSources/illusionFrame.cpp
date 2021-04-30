/*!
@file illusionFrame.cpp
@brief 錯視フレームの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void illusionFrame::SetPosition(Vec2 pos) {
		GetComponent<Transform>()->SetPosition((Vec3)pos);
	}

	void illusionFrame::OnCreate() {
		Col4 color(0.0f, 0.0f, 0.0f, 1.0f);
		auto halfLength = m_boxLength / 2.0f;
		auto halfHeight = m_boxHeight / 2.0f;
		auto halfThickness = m_lineThickness / 2.0f;
		auto tumourLength = 30.0f;
		vector<LineSpriteParam> baseParams = {
			//ボックスの部分
			{m_boxLength,m_lineThickness,color,Align::Horizontal::Center,Vec2(0.0f,+halfHeight - halfThickness), 0.0f},
			{m_boxLength,m_lineThickness,color,Align::Horizontal::Center,Vec2(0.0f,-halfHeight + halfThickness), 0.0f},
			{m_boxHeight,m_lineThickness,color,Align::Horizontal::Center,Vec2(-halfLength + halfThickness,0.0f),90.0f},
			{m_boxHeight,m_lineThickness,color,Align::Horizontal::Center,Vec2(+halfLength - halfThickness,0.0f),90.0f},
			//右のやつ
			{tumourLength,m_lineThickness,color,Align::Horizontal::Left,Vec2(+halfLength,0.0f),0.0f},
			//左のやつ
			{tumourLength,m_lineThickness,color,Align::Horizontal::Right,Vec2(-halfLength,0.0f),0.0f}
		};
		vector<LineSpriteParam> arrowParams = {
			//右
			{tumourLength,m_lineThickness,color,Align::Horizontal::Left,Vec2(+halfLength + tumourLength,0.0f),135.0f},
			{tumourLength,m_lineThickness,color,Align::Horizontal::Left,Vec2(+halfLength + tumourLength,0.0f),-135.0f},
			//左
			{tumourLength,m_lineThickness,color,Align::Horizontal::Right,Vec2(-halfLength - tumourLength,0.0f),135.0f},
			{tumourLength,m_lineThickness,color,Align::Horizontal::Right,Vec2(-halfLength - tumourLength,0.0f),-135.0f}
		};

		auto stage = GetStage();
		for (auto& param : baseParams) {
			auto line = stage->AddGameObject<LineSprite>(param.Horizontal);
			line->SetStatus(param.Length, param.Thickness, param.Color);
			line->SetPosition(param.Position);
			line->SetRotation(param.Rotation);
			line->GetComponent<Transform>()->SetParent(GetThis<illusionFrame>());
			m_baseSprites.push_back(line);
		}
		for (auto& param : arrowParams) {
			auto line = stage->AddGameObject<LineSprite>(param.Horizontal);
			line->SetStatus(param.Length, param.Thickness, param.Color);
			line->SetPosition(param.Position);
			line->SetRotation(param.Rotation);
			line->GetComponent<Transform>()->SetParent(GetThis<illusionFrame>());
			m_arrowSprites.push_back(line);
		}
	}

	void illusionFrame::SetDrawActive(bool flg) {
		for (auto& base : m_baseSprites) {
			base->SetDrawActive(flg);
		}
		for (auto& arrow : m_arrowSprites) {
			arrow->SetDrawActive(flg);
		}
	}
	void illusionFrame::SetItemActive(bool flg) {
		for (int i = 0; i < m_arrowSprites.size(); i++) {
			int key = i % 2 != 0 ? 1 : -1;
			if (flg) {
				m_arrowSprites[i]->SetRotation(45.0f * key);
			}
			else {
				m_arrowSprites[i]->SetRotation(135.0f * key);
			}
		}
	}

}
//end basecross