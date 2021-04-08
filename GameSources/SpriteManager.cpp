///*!
//@file SpriteManager.cpp
//@brief �X�v���C�g�Ǘ��N���X
//*/
//
//#include "stdafx.h"
//#include "Project.h"
//
//namespace basecross {
//	void SpriteManager::OnCreate() {
//		//�g����������Ȃ��̂�GameStage�^�ɃL���X�g
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
//			//�G���[
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
//		if (m_objs[1]) { //���łɍ���Ă���Ƃ�
//			m_objs[1]->SetDrawActive(flg);
//		}
//		else if(flg){ //�܂�����Ă��Ȃ��Ƃ��ɗL���̎�
//			CreateOutline();
//		}
//		else { //�܂�����Ă��Ȃ��Ƃ��ɖ����̎�
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
//		//�傫���͓����Ȃ̂łƂ肠����x��Ԃ�
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
