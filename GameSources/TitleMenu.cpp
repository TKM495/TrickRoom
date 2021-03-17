/*!
@file TitleMenu.cpp
@brief タイトルのメニュー管理クラスの実体
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

		//-1なのは配列に合わせるため
		m_menuNum = (int)m_menuElement.size() - 1;

		//デバッグ用の文字列を表示するためのコンポーネントを追加
		auto ssComp = AddComponent<StringSprite>();
		ssComp->SetBackColor(Col4(0.0f, 0.0f, 0.0f, 0.5)); //文字列の表示領域の背景色を変更
		ssComp->SetTextRect(Rect2D<float>(10, 10, 300, 200)); //文字列表示領域のサイズを変更
	}

	void TitleMenu::OnUpdate() {
		//コントローラの取得
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
