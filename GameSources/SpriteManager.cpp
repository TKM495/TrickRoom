///*!
//@file SpriteManager.cpp
//@brief スプライト管理クラス
//*/
//
//#include "stdafx.h"
//#include "Project.h"
//
//namespace basecross {
//	void SpriteManager::OnCreate() {
//		//使うかもしれないのでGameStage型にキャスト
//		auto stage = dynamic_pointer_cast<GameStage>(GetStage());
//		switch (m_type)
//		{
//		case SpriteType::String:
//			m_objs[0] = stage->AddGameObject<StringSprite2>(
//				m_value,
//				m_horizontal,
//				m_vertical,
//				m_colors[0]
//				);
//			m_objs[0]->SetDrawLayer(1);
//			break;
//		case SpriteType::Image:
//			break;
//		case SpriteType::Number:
//			m_objs[0] = stage->AddGameObject<Numbers>(
//				(int)_wtof(m_value.c_str()),
//				m_colors[0]
//				);
//			m_objs[0]->SetDrawLayer(1);
//			break;
//		default:
//			//エラー
//			break;
//		}
//	}
//
//	void SpriteManager::CreateOutline() {
//		auto stage = dynamic_pointer_cast<GameStage>(GetStage());
//		switch (m_type)
//		{
//		case SpriteType::String:
//			m_objs[1] = stage->AddGameObject<StringSprite2>(
//				m_value,
//				m_horizontal,
//				m_vertical,
//				m_colors[1]
//				);
//			{
//				auto outline = dynamic_pointer_cast<StringSprite2>(m_objs[1]);
//				outline->SetSize(m_outlineSize + m_size);
//			}
//			break;
//		case SpriteType::Image:
//			break;
//		case SpriteType::Number:
//			m_objs[1] = stage->AddGameObject<Numbers>(
//				(int)_wtof(m_value.c_str()),
//				m_colors[1]
//				);
//			{
//				auto outline = dynamic_pointer_cast<Numbers>(m_objs[1]);
//				outline->SetSize(m_outlineSize + m_size);
//			}
//			break;
//		default:
//			break;
//		}
//
//	}
//
//	void SpriteManager::IsOutline(bool flg) {
//		if (m_objs[1]) { //すでに作られているとき
//			m_objs[1]->SetDrawActive(flg);
//		}
//		else if(flg){ //まだ作っていないときに有効の時
//			CreateOutline();
//		}
//		else { //まだ作っていないときに無効の時
//
//		}
//		m_bOutline = flg;
//	}
//
//	void SpriteManager::SetColor(int num, Col4 color) {
//
//	}
//
//	void SpriteManager::SetAlignHorizontal(Align::Horizontal hor) {
//
//	}
//
//	void SpriteManager::SetAlignVertical(Align::Vertical ver) {
//
//	}
//
//	void SpriteManager::SetSize(float size) {
//		switch (m_type)
//		{
//		case SpriteType::String:
//		{
//			auto obj = dynamic_pointer_cast<StringSprite2>(m_objs[0]);
//			obj->SetSize(size);
//			if (m_objs[1]) {
//				auto obj = dynamic_pointer_cast<StringSprite2>(m_objs[1]);
//				obj->SetSize(size + m_outlineSize);
//			}
//		}
//			break;
//		case SpriteType::Image:
//			break;
//		case SpriteType::Number:
//			break;
//		default:
//			break;
//		}
//		GetComponent<Transform>()->SetScale(Vec3(size));
//	}
//
//	void SpriteManager::SetPos(Vec3 pos) {
//		switch (m_type)
//		{
//		case SpriteType::String:
//		{
//			auto obj = dynamic_pointer_cast<StringSprite2>(m_objs[0]);
//			obj->SetPos(pos);
//			if (m_bOutline) {
//				auto obj = dynamic_pointer_cast<StringSprite2>(m_objs[1]);
//				obj->SetPos(pos);
//			}
//		}
//			break;
//		case SpriteType::Image:
//			break;
//		case SpriteType::Number:
//			break;
//		default:
//			break;
//		}
//	}
//
//	float SpriteManager::GetSize() {
//		//大きさは同じなのでとりあえずxを返す
//		return GetComponent<Transform>()->GetScale().x;
//	}
//
//	Vec3 SpriteManager::GetPos() {
//		return GetComponent<Transform>()->GetPosition();
//	}
//
//	void SpriteManager::SetDrawSprite(bool flg) {
//		m_objs[0]->SetDrawActive(flg);
//		if (m_objs[1]) {
//			m_objs[1]->SetDrawActive(flg);
//		}
//	}
//}
////end basecross
