#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Debug::OnCreate() {
		//デバッグ用の文字列を表示するためのコンポーネントを追加
		auto ssComp = AddComponent<StringSprite>();
		ssComp->SetBackColor(Col4(0.0f, 0.0f, 0.0f, 0.5)); //文字列の表示領域の背景色を変更
		ssComp->SetTextRect(Rect2D<float>(10, 10, 300, 200)); //文字列表示領域のサイズを変更
	}

	void Debug::OnUpdate() {
		auto ssComp = GetComponent<StringSprite>();
		wss.str(L"");
		wss << m_wstr << endl;
		ssComp->SetText(wss.str());
	}
}