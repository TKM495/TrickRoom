/*!
@file TitleMenu.h
@brief �^�C�g���̃��j���[�Ǘ��N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TitleMenu :public BaseMenu {
	public:
		TitleMenu(const shared_ptr<Stage>& stage)
			:BaseMenu(stage)
		{}

		virtual void OnCreate()override;
	};
}
//end basecross