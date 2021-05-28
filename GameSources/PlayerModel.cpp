#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void PlayerModel::OnCreate() {
		auto drawComp = AddComponent<PNTBoneModelDraw>();
		drawComp->SetMeshResource(L"PlayerModel");
		drawComp->SetDiffuse(Col4(0.2f));
		drawComp->SetEmissive(Col4(0.7f));
		drawComp->AddAnimation(L"Run", 0, 25, true, 40.0f);
		//drawComp->ChangeCurrentAnimation(L"Run");

		auto shadow = AddComponent<Shadowmap>();
		shadow->SetMeshResource(L"PlayerModel");

		auto transComp = GetComponent<Transform>();
		transComp->SetScale(Vec3(2.0f));

		m_timer.SetCountTime(0.28f);
		m_timer.Reset();
	}
	void PlayerModel::OnUpdate() {
		auto bLeapFlg = dynamic_pointer_cast<MainCamera>(OnGetDrawCamera())->GetbLeapFlg();
		if (bLeapFlg) {
			return;
		}
		auto stage = GetTypeStage<GameStage>();
		auto delta = App::GetApp()->GetElapsedTime();
		auto playerDiffPos = m_player->GetDiffPos();
		auto playerSpeed = m_player->GetNowMoveSp();
		//�ړ��������S���Ă��Ȃ����N���A��ԂɂȂ��Ă��Ȃ����������Ă��Ȃ��Ƃ�
		auto state = stage->GetState();

		// ���ړ����聄
		// �v���C��(���[�U�[������ł���Ƃ�)�̓f�o�C�X�̓��͂Ŕ��f��
		// ����ȊO(�����ړ��Ȃ�)�̎��͈ʒu�̍����Ŕ��f����
		bool bMove = false;
		switch (state)
		{
		case GameStage::GameState::PLAYING:
			if (playerSpeed.lengthSqr() > 0.0f) {
				bMove = true;
			}
			break;
		default:
			if (playerDiffPos.lengthSqr() > 0.0f) {
				bMove = true;
			}
			break;
		}

		if (bMove && !m_player->GetbRespawn() &&
			playerDiffPos.y > -0.05f) {
			Motion(delta);
		}
	}

	void PlayerModel::Motion(float delta) {
		auto drawComp = GetComponent<PNTBoneModelDraw>();
		drawComp->UpdateAnimation(delta);
		if (m_timer.Count()) {
			auto audio = App::GetApp()->GetXAudio2Manager();
			audio->Start(L"WalkSE", 0, 0.5f);
			m_timer.Reset();
		}
	}
}