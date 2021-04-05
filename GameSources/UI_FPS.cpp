/*!
@file UI_FPS.cpp
@brief フレームレートUI実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void UI_FPS::OnCreate() {
		SetDrawLayer(10);

		//デバッグ用の文字列を表示するためのコンポーネントを追加
		auto ssComp = AddComponent<StringSprite>();
		ssComp->SetBackColor(Col4(0.0f, 0.0f, 0.0f, 0.0f)); //文字列の表示領域の背景色を変更
		ssComp->SetTextRect(Rect2D<float>(10, 10, 100, 50)); //文字列表示領域のサイズを変更
		ssComp->SetText(L"");
	}

	void UI_FPS::OnUpdate() {
		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring FPS(L"FPS: ");
		FPS += Util::UintToWStr(fps);

		auto ssComp = GetComponent<StringSprite>();
		ssComp->SetText(FPS);
	}
}
//end basecross
