/*!
@file TitleMenu.h
@brief タイトルのメニュー管理クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TitleMenu :public BaseMenu {
		//std::wstringstream wss; //デバッグ用文字列

	public:
		TitleMenu(const shared_ptr<Stage>& stage)
			:BaseMenu(stage)
		{}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}
//end basecross
