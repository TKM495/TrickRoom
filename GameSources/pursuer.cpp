/*!
@file pursuer.cpp
@brief
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Pursuer::OnCreate()
	{

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetDiffuse(Col4(0.0f, 0.0f, 0.0f, 0.8f));

		auto transComponent = GetComponent<Transform>();
		transComponent->SetPosition(10.0f, 3.0f, 0.0f);
		transComponent->SetScale(1, 10, 10);

		SetAlphaActive(true);
	}

	Vec3 Pursuer::MoveVec()
	{
		auto stage = GetStage();

		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();

		const auto& app = App::GetApp();
		float ElapsedTime = app->GetElapsedTime();

		Vec3 moveVec = Vec3(-1.0f, 0.0f, 0.0f);
		return moveVec * m_Speed * ElapsedTime;


	}


	void Pursuer::OnUpdate()
	{
		Move();
	}

	void Pursuer::Move()
	{
		auto stage = GetStage();

		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetWorldPosition();

		const auto& app = App::GetApp();
		float ElapsedTime = app->GetElapsedTime();

		pos += MoveVec();

		transComp->SetWorldPosition(pos);

	}
}