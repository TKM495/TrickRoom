#include "stdafx.h"
#include "Project.h"

namespace basecross {
	GoalModel::GoalModel(const std::shared_ptr<Stage>& stage,
		ObjectParam param)
		: GameObject(stage), m_param(param), m_bOpen(false), m_bOnce(false)
	{}

	void GoalModel::OnCreate()
	{
		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_param.position);
		transComp->SetScale(m_param.scale);
		transComp->SetRotation(m_param.rotation);

		auto drawComp = AddComponent<BcPNTBoneModelDraw>();
		drawComp->SetMultiMeshResource(L"Goal");
		drawComp->SetDiffuse(Col4(0.5f, 0.3f, 0.0f, 1.0f));
		drawComp->AddAnimation(L"Open", 0, 30, false, 60.0f);
		drawComp->AddAnimation(L"Close", 30, 60, false, 60.0f);
	}

	void GoalModel::OnUpdate() {
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto playerPos = player->GetComponent<Transform>()->GetPosition();
		auto drawComp = GetComponent<BcPNTBoneModelDraw>();
		float delta = App::GetApp()->GetElapsedTime();

		auto dir = playerPos - m_param.position;
		if (dir.length() < 3.0f) {
			drawComp->UpdateAnimation(delta);
			m_bOpen = true;
		}

		if (m_bOpen && !m_bOnce) {
			auto audio = App::GetApp()->GetXAudio2Manager();
			audio->Start(L"DoorOpenSE", 0, 0.1f);
			m_bOnce = true;
		}
	}
}
