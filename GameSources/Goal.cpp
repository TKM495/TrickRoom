#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Goal::Goal(const std::shared_ptr<Stage>& stage,
		const wstring& line)
		: StageObject(stage)
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

	void Goal::OnCreate()
	{
		auto drawComp = AddComponent<BcPNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetDiffuse(Col4(0.5f, 0.3f, 0.0f, 1.0f));

		auto collComp = AddComponent<CollisionObb>();
		collComp->SetFixed(true);

		auto scene = App::GetApp()->GetScene<Scene>();
		if (scene->GetDebugState() == DebugState::Debug) {
			collComp->SetDrawActive(true);
		}

		Vec3 scale(
			m_scale.x * 1.0f,
			m_scale.y * 2.0f,
			m_scale.z * 0.2f
		);

		m_scale = scale;
		StageObject::OnCreate();
		AddTag(L"Goal");
	}
}
