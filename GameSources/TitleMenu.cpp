/*!
@file TitleMenu.cpp
@brief �^�C�g���̃��j���[�Ǘ��N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TitleMenu::OnCreate() {
		MenuElement titleMenu[]{
			{Vec2(0.0f,0.0f),L"NextStage"},
			{Vec2(1.0f,1.0f),L"Retry"},
			{Vec2(2.0f,2.0f),L"StageSelect"}
		};

		for (auto element : titleMenu) {
			m_menuElement.push_back(element);
		}

		//-1�Ȃ͔̂z��ɍ��킹�邽��
		m_menuNum = (int)m_menuElement.size() - 1;

		//�f�o�b�O�p�̕������\�����邽�߂̃R���|�[�l���g��ǉ�
		auto ssComp = AddComponent<StringSprite>();
		ssComp->SetBackColor(Col4(0.0f, 0.0f, 0.0f, 0.5)); //������̕\���̈�̔w�i�F��ύX
		ssComp->SetTextRect(Rect2D<float>(10, 10, 300, 200)); //������\���̈�̃T�C�Y��ύX
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

		auto menuElement = m_menuElement[m_nowMenuNum];

		wss.str(L"");
		wss << L"Num : " << m_menuNum << endl;
		wss << L"Pos :" << menuElement.pos.x << L", " <<
			menuElement.pos.y << endl;
		wss << L"Name : " << menuElement.name << endl;
		GetComponent<StringSprite>()->SetText(wss.str());
	}
}
//end basecross
