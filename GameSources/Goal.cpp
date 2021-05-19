#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Goal::Goal(const shared_ptr<Stage>& stage,
		const wstring& line)
		:StageObject(stage)
	{
		vector<wstring> tokens;
		Util::WStrToTokenVector(tokens, line, L',');
		m_position = Vec3(
			(float)_wtof(tokens[1].c_str()),
			(float)_wtof(tokens[2].c_str()),
			(float)_wtof(tokens[3].c_str())
		);
		m_scale = Vec3(
			(float)_wtof(tokens[4].c_str()),
			(float)_wtof(tokens[5].c_str()),
			(float)_wtof(tokens[6].c_str())
		);
		m_rotation = Vec3(
			XMConvertToRadians((float)_wtof(tokens[7].c_str())),
			XMConvertToRadians((float)_wtof(tokens[8].c_str())),
			XMConvertToRadians((float)_wtof(tokens[9].c_str()))
		);
	}

	void Goal::OnCreate() {
		auto stage = GetTypeStage<GameStage>();
		auto goalPos = m_position;
		ObjectParam param = {
			goalPos,
			m_scale,
			m_rotation
		};
		//ここで回転を適用
		StageObject::ObjectSetUp();
		stage->AddGameObject<GoalModel>(param);
		m_scale = Vec3(2.0f, 2.0f, 1.5f);
		auto transComp = GetComponent<Transform>();
		auto forword = transComp->GetForword();
		forword *= 0.75f;
		m_position += Vec3(forword.x, 1.0f, forword.z);
		stage->AddGameObject<GoalPoint>(param);
		//ここで全ての変更を適用
		StageObject::ObjectSetUp();

		forword = transComp->GetForword();
		ObjectPositionForward opf(goalPos, forword);
		auto camera = dynamic_pointer_cast<MainCamera>(OnGetDrawCamera());
		camera->SetGoalPosForward(opf);
		stage->SetGoalPosForward(opf);

		auto collComp = AddComponent<CollisionObb>();
		collComp->SetFixed(true);
		collComp->SetAfterCollision(AfterCollision::None);

		auto scene = App::GetApp()->GetScene<Scene>();
		if (scene->GetDebugState() == DebugState::Debug) {
			collComp->SetDrawActive(true);
		}
		AddTag(L"Goal");
	}
}
//end basecross