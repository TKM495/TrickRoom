/*!
@file StageParent.cpp
@brief �X�e�[�W�̐e����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void StageParent::OnCreate() {
		GetStage()->SetSharedGameObject(L"StageParent", GetThis<StageParent>());
	}
}
//end basecross
