/*!
@file pursuer.cpp
@brief
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Pursuer::Pursuer(const std::shared_ptr<Stage>& stage,
		const wstring& line)
		: StageObject(stage), m_Speed(6)
	{
		vector<wstring> tokens;
		Util::WStrToTokenVector(tokens, line, L',');
		m_position = Vec3(
			(float)_wtof(tokens[1].c_str()),
			(float)_wtof(tokens[2].c_str()),
			(float)_wtof(tokens[3].c_str())
		);
		auto scale = Vec3(
			(float)_wtof(tokens[4].c_str()),
			(float)_wtof(tokens[5].c_str()),
			(float)_wtof(tokens[6].c_str())
		);
		m_scale = Vec3(
			scale.x * 5.0f,
			scale.y * 9.9f,
			scale.z * 9.9f
		);
		m_rotation = Vec3(0.0f);
	}
	void Pursuer::OnCreate()
	{
		GetStage()->SetSharedGameObject(L"Pursuer", GetThis<Pursuer>());

		auto drawComp = AddComponent<PCTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetDiffuse(Col4(0.0f, 0.0f, 0.0f, 0.6f));

		m_position.x += dynamic_pointer_cast<GameStage>(GetStage())->GetStartOffset();
		auto transComponent = GetComponent<Transform>();
		transComponent->SetPosition(m_position);
		transComponent->SetScale(m_scale);

		SetAlphaActive(true);
	}

	Vec3 Pursuer::MoveVec()
	{
		auto stage = dynamic_pointer_cast<GameStage>(GetStage());

		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();

		const auto& app = App::GetApp();
		float ElapsedTime = app->GetElapsedTime();

		Vec3 moveVec;
		switch (stage->GetState())
		{
		case GameStage::GameState::PAUSE:
			moveVec = Vec3(0.0f);
			break;
		default:
			moveVec = Vec3(-1.0f, 0.0f, 0.0f);
			break;
		}
		return moveVec * m_Speed * ElapsedTime;
	}


	void Pursuer::OnUpdate()
	{
		auto camera = dynamic_pointer_cast<MainCamera>(GetStage()->GetView()->GetTargetCamera());
		if (!camera->GetbLeapFlg()) {
			Move();
		}
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

	Vec3 Pursuer::GetPos() {
		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();
		auto scale = transComp->GetScale();
		pos.x += -scale.x / 2.0f;
		return pos;
	}

}