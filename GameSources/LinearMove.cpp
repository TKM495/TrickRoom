#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void LinerMove::OnCreate() {
		distance_two = (start - end).length();
	}

	void LinerMove::Excute() {
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();

		if (Flg == false)
		{
			A += delta * speed;
		}
		else
		{
			A -= delta * speed;
		}

		float present_Location = A / distance_two;

		if (present_Location >= 1)
		{
			Flg = true;
		}

		if (present_Location <= 0)
		{
			Flg = false;
		}

		auto ptrTrans = GetGameObject()->GetComponent<Transform>();
		ptrTrans->SetPosition(MyMath::Leap(start, end, present_Location));
	}
}