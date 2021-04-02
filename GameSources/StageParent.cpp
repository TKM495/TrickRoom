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

	void StageParent::OnUpdate() {
		//auto transComp = GetComponent<Transform>();
		//auto pos = transComp->GetPosition();
		//auto speed = -6.0f * App::GetApp()->GetElapsedTime();
		//pos += Vec3(speed, 0.0f, 0.0f);
		//transComp->SetPosition(pos);
	}
}
//end basecross
