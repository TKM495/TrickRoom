#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void PlayerModel::OnCreate() {
		auto drawComp = AddComponent<PNTBoneModelDraw>();
		drawComp->SetMeshResource(L"PlayerModel");
		drawComp->AddAnimation(L"Run", 0, 25, true, 40.0f);
		//drawComp->ChangeCurrentAnimation(L"Run");

		auto shadow = AddComponent<Shadowmap>();
		shadow->SetMeshResource(L"PlayerModel");
	}
	void PlayerModel::OnUpdate() {
		auto bLeapFlg = dynamic_pointer_cast<MainCamera>(OnGetDrawCamera())->GetbLeapFlg();
		if (bLeapFlg) {
			return;
		}

		auto delta = App::GetApp()->GetElapsedTime();
		auto drawComp = GetComponent<PNTBoneModelDraw>();
		auto playerSpeed = m_player->GetNowMoveSp();
		if (playerSpeed.lengthSqr() > 0.0f && !m_player->GetbRespawn()) {
			drawComp->UpdateAnimation(delta);
			if (m_delta > 0.28f) {
				auto audio = App::GetApp()->GetXAudio2Manager();
				audio->Start(L"WalkSE", 0, 0.5f);
				m_delta = 0.0f;
			}
		}
		m_delta += delta;
	}
}