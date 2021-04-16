/*!
@file ResultMenu.h
@brief リザルトのメニュー管理クラス
*/

#pragma once
#include "stdafx.h"
#include "BaseMenu.h"

namespace basecross {
	class ResultMenu :public BaseMenu {
		int m_stageNum;
		bool m_bStateFlg;
	public:
		ResultMenu(const shared_ptr<Stage>& stage,
			bool flg)
			:BaseMenu(stage),
			m_bStateFlg(flg)
		{
			SetMenuDirection(MenuDirection::Horizontal);
		}

		virtual void OnCreate()override;
		virtual void OnPushButton(MenuElement element)override;
		virtual void BeforeReset()override;
	};
}
//end basecross
