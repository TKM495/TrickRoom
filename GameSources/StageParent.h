/*!
@file StageParent.h
@brief �X�e�[�W�̐e
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class StageParent :public GameObject {
	public:
		StageParent(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		virtual void OnCreate()override;
	};

}
//end basecross
