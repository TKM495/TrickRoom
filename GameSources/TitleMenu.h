/*!
@file TitleMenu.h
@brief �^�C�g���̃��j���[�Ǘ��N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TitleMenu :public BaseMenu {
		//std::wstringstream wss; //�f�o�b�O�p������

	public:
		TitleMenu(const shared_ptr<Stage>& stage)
			:BaseMenu(stage)
		{}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}
//end basecross
