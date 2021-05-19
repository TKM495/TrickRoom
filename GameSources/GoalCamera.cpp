#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void GoalCamera::OnCreate() {
		//auto gameStage = App::GetApp()->GetScene<Scene>()->GetActiveTypeStage<GameStage>();

		//auto goalTrans = gameStage->GetGoalPosForward();
		//goalTrans.origin.y += 0.5f;
		//SetAt(goalTrans.origin);
		//auto dir = goalTrans.dir * 5.0f;
		//auto eye = goalTrans.origin + dir;
		//SetEye(eye);

		SetAt(Vec3(-7.5f, 0.5f, 0.0f));
		SetEye(Vec3(0.0f, 0.5f, 0.0f));
	}
}
//end basecross