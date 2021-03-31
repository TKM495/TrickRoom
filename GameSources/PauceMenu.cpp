/*!
@file PauceMenu.cpp
@brief ポーズ画面のメニュー管理クラスの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void PauceMenu::OnCreate() {
		MenuElement PauceMenu[]{
			{Vec2(0.0f,0.0f),L"GameStart",L"ToGameStage"},
			{Vec2(0.0f,-100.0f),L"Exit",L"ToExit"},
		};

		for (auto element : PauceMenu) {
			m_menuElement.push_back(element);
		}
		SetUpMenu();
	}
}
//end basecross
