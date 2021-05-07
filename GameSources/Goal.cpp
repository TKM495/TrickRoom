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
		ObjectParam param = {
			m_position,
			m_scale,
			m_rotation
		};
		stage->AddGameObject<GoalModel>(param);
		m_position.y += 1.0f;
		m_scale = Vec3(2.0f, 2.0f, 0.2);
		StageObject::ObjectSetUp();
		stage->SetGoalX(m_position.x);

		auto collComp = AddComponent<CollisionObb>();
		collComp->SetFixed(true);
		auto scene = App::GetApp()->GetScene<Scene>();
		if (scene->GetDebugState() == DebugState::Debug) {
			collComp->SetDrawActive(true);
		}
		AddTag(L"Goal");
	}
}
//end basecross