/*!
@file Pause.h
@brief ポーズシステム
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Pause :public GameObject {
		weak_ptr<StringSprite2> m_titleObj;
		weak_ptr<PauseMenu> m_menuObj;
		weak_ptr<FrameSprite> m_frameObj;
	public:
		Pause(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		virtual void OnCreate()override;

		void IsActive(bool flg);
	};
}
//end basecross
