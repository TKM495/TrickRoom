/*!
@file ResultMenu.h
@brief リザルトのメニュー管理クラス
*/

#pragma once
#include "stdafx.h"
#include "BaseMenu.h"

namespace basecross {
	class ResultMenu :public BaseMenu {
	public:
		ResultMenu(const shared_ptr<Stage>& stage)
			:BaseMenu(stage)
		{
			m_dir = MenuDirection::Horizontal;
		}

		virtual void OnCreate()override;
	};
}
//end basecross
