/*!
@file TitleMenu.h
@brief タイトルのメニュー管理クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TitleMenu :public BaseMenu {
	public:
		TitleMenu(const shared_ptr<Stage>& stage)
			:BaseMenu(stage)
		{
			SetMenuDirection(MenuDirection::Vertical);
		}

		virtual void OnCreate()override;
		virtual void OnPushButton()override;
	};
}
//end basecross
