/*!
@file TitleMenu.cpp
@brief �^�C�g���̃��j���[�Ǘ��N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TitleMenu::OnCreate() {
		MenuElement titleMenu[]{
			{Vec2(0.0f,0.0f),L"GameStart",L"ToGameStage"},
			{Vec2(0.0f,-100.0f),L"Exit",L"test"},
		};

		for (auto element : titleMenu) {
			m_menuElement.push_back(element);
		}

		//-1�Ȃ͔̂z��ɍ��킹�邽��
		m_menuNum = (int)m_menuElement.size() - 1;

		auto& stage = GetStage();
		for (auto& element : m_menuElement) {
			auto str = stage->AddGameObject<StringSprite2>(element.name);
			str->GetComponent<Transform>()->SetPosition((Vec3)element.pos);
			m_spriteMenu.push_back(str);
		}

		////�f�o�b�O�p�̕������\�����邽�߂̃R���|�[�l���g��ǉ�
		//auto ssComp = AddComponent<StringSprite>();
		//ssComp->SetBackColor(Col4(0.0f, 0.0f, 0.0f, 0.5)); //������̕\���̈�̔w�i�F��ύX
		//ssComp->SetTextRect(Rect2D<float>(10, 10, 300, 200)); //������\���̈�̃T�C�Y��ύX
		m_cursor = GetStage()->AddGameObject<Cursor>();
	}

	void TitleMenu::OnUpdate() {
		//�R���g���[���̎擾
		const auto& pad = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_UP &&
			m_nowMenuNum > 0) {
			m_nowMenuNum--;
		}
		if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN &&
			m_nowMenuNum < m_menuNum) {
			m_nowMenuNum++;
		}

		auto element = m_menuElement[m_nowMenuNum];

		auto transComp = m_cursor->GetComponent<Transform>();
		transComp->SetPosition((Vec3)element.pos);


		if (pad.wPressedButtons & XINPUT_GAMEPAD_A) {
			//���b�Z�[�W�𑗂�(�����҂�)
			//PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), element.sendMsg);
		}
	}
}
//end basecross
