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
			{Vec2(0.0f,-100.0f),L"Exit",L"ToExit"},
		};

		for (auto element : titleMenu) {
			m_menuElement.push_back(element);
		}
		SetUpMenu();
	}
}
//end basecross