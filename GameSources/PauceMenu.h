/*!
@file PauceMenu.h
@brief ポーズ画面のメニュー管理クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PauceMenu :public BaseMenu {
	public:
		PauceMenu(const shared_ptr<Stage>& stage)
			:BaseMenu(stage)
		{}

		virtual void OnCreate()override;
	};
}
//end basecross
