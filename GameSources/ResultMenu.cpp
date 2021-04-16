/*!
@file ResultMenu.cpp
@brief リザルトのメニュー管理クラスの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void ResultMenu::OnCreate() {
		auto scene = App::GetApp()->GetScene<Scene>();
		m_stageNum = scene->GetStageNum();
		auto maxStage = scene->GetMaxStage();

		MenuElement element = { Vec2(-400.0f,-330.0f),L"Retry",L"ToGameStage" };
		PushBackElement(element);

		element = { Vec2(0.0f,-330.0f),L"StageSelect",L"ToSelectStage" };
		PushBackElement(element);

		if (m_bStateFlg && m_stageNum < maxStage) {
			element = { Vec2(400.0f, -330.0f), L"NextStage", L"ToGameStage" };
			PushBackElement(element);
		}

		SetUpMenu<StringSprite2, Cursor>();
	}

	void ResultMenu::OnPushButton(MenuElement element) {
		auto fade = GetStage()->GetSharedGameObject<Fade>(L"Fade");
		SetDelayTime(fade->GetFadeTime());
		fade->FadeOut();
		if (element.name == L"NextStage") {
			m_stageNum++;
		}
		BaseMenu::OnPushButton();
	}

	void ResultMenu::BeforeReset() {
		App::GetApp()->GetScene<Scene>()->SetStageNum(m_stageNum);
	}
}
//end basecross
