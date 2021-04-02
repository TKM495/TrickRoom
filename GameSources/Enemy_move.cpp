/*!
@file Player.cpp
@brief “G‚È‚Ç‚ÌŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"
#include "MyMath.h"

namespace basecross {

	void Enemy_move::OnCreate() 
	{
		auto drawComp = AddComponent<BcPNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");

		distance_two = (start - end).length();
	}

	void Enemy_move::OnUpdate()
	{
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

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(MyMath::Leap(start, end, present_Location));
	}
}