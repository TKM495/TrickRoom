/*!
@file StageParent.cpp
@brief ステージの親実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void StageParent::OnCreate() {
		GetStage()->SetSharedGameObject(L"StageParent", GetThis<StageParent>());
	}
}
//end basecross
