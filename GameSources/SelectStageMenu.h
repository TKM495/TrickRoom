/*!
@file SelectStageMenu.h
@brief ステージセレクトのメニュークラス
*/

#pragma once
#include "stdafx.h"
#include "BaseMenu.h"

namespace basecross {
	class SelectStageMenu :public BaseMenu {
	public:
		SelectStageMenu(const shared_ptr<Stage>& stage)
			:BaseMenu(stage)
		{
			m_dir = MenuDirection::Vertical;
		}

		virtual void OnCreate()override;
		virtual void OnPushButton()override;
	};
}
//end basecross
