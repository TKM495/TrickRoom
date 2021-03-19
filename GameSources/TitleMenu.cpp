/*!
@file TitleMenu.cpp
@brief タイトルのメニュー管理クラスの実体
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

		//-1なのは配列に合わせるため
		m_menuNum = (int)m_menuElement.size() - 1;

		auto& stage = GetStage();
		for (auto& element : m_menuElement) {
			auto str = stage->AddGameObject<StringSprite2>(element.name);
			str->GetComponent<Transform>()->SetPosition((Vec3)element.pos);
			m_spriteMenu.push_back(str);
		}

		////デバッグ用の文字列を表示するためのコンポーネントを追加
		//auto ssComp = AddComponent<StringSprite>();
		//ssComp->SetBackColor(Col4(0.0f, 0.0f, 0.0f, 0.5)); //文字列の表示領域の背景色を変更
		//ssComp->SetTextRect(Rect2D<float>(10, 10, 300, 200)); //文字列表示領域のサイズを変更
		m_cursor = GetStage()->AddGameObject<Cursor>();
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

		auto element = m_menuElement[m_nowMenuNum];

		auto transComp = m_cursor->GetComponent<Transform>();
		transComp->SetPosition((Vec3)element.pos);


		if (pad.wPressedButtons & XINPUT_GAMEPAD_A) {
			//メッセージを送る(実装待ち)
			//PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), element.sendMsg);
		}
	}
}
//end basecross
