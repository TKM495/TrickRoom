/*!
@file PauseMenu.h
@brief �|�[�Y��ʂ̃��j���[�Ǘ��N���X
*/

#pragma once
#include "stdafx.h"
#include "BaseMenu.h"

namespace basecross {
	class PauseMenu :public BaseMenu {
	public:
		PauseMenu(const shared_ptr<Stage>& stage)
			:BaseMenu(stage)
		{
			SetMenuDirection(MenuDirection::Vertical);
		}

		virtual void OnCreate()override;
		virtual void OnPushButton(wstring mes)override;
		virtual void SendEvent(wstring mes)override;
		virtual void PlayDecisionSE(wstring mes)override;
	};
}
//end basecross
