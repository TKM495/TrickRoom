#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void PlayerModel::OnCreate() {
		auto drawComp = AddComponent<PNTBoneModelDraw>();
		drawComp->SetMeshResource(L"PlayerModel");
		drawComp->SetDiffuse(Col4(0.1f));
		drawComp->SetEmissive(Col4(0.9f));

		drawComp->AddAnimation(L"Run", 0, 25, true, 40.0f);
		drawComp->AddAnimation(L"Goal", 26, 65 - 26, false, 30.0f);
		drawComp->AddAnimation(L"Normal", 65, 1, false, 1.0f);
		drawComp->AddAnimation(L"Damage", 67, 1, false, 1.0f);

		auto shadow = AddComponent<Shadowmap>();
		shadow->SetMeshResource(L"PlayerModel");

		//���f���̑傫�������p
		auto transComp = GetComponent<Transform>();
		transComp->SetScale(Vec3(1.0f));

		//�X�e�[�g�}�V���̍\�z
		m_StateMachine.reset(new StateMachine<PlayerModel>(GetThis<PlayerModel>()));
		//�����X�e�[�g�̐ݒ�
		m_StateMachine->ChangeState(PlayerModelRun::Instance());
	}
	void PlayerModel::OnUpdate() {
		m_StateMachine->Update();
	}

	void PlayerModel::RunInit() {
		auto drawComp = GetComponent<PNTBoneModelDraw>();
		drawComp->ChangeCurrentAnimation(L"Run");
		m_timer.SetCountTime(0.28f);
		m_timer.Reset();
	}
	void PlayerModel::RunBehavior() {
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
	void PlayerModel::DamageInit() {
		auto drawComp = GetComponent<PNTBoneModelDraw>();
		drawComp->ChangeCurrentAnimation(L"Damage");
	}
	void PlayerModel::DamageBehavior() {
		auto drawComp = GetComponent<PNTBoneModelDraw>();
		drawComp->UpdateAnimation(App::GetApp()->GetElapsedTime());
	}
	void PlayerModel::NormalInit() {
		auto drawComp = GetComponent<PNTBoneModelDraw>();
		drawComp->ChangeCurrentAnimation(L"Normal");
	}
	void PlayerModel::NormalBehavior() {
		auto drawComp = GetComponent<PNTBoneModelDraw>();
		drawComp->UpdateAnimation(App::GetApp()->GetElapsedTime());
	}
	void PlayerModel::GoalInit() {
		auto drawComp = GetComponent<PNTBoneModelDraw>();
		drawComp->ChangeCurrentAnimation(L"Goal");
		m_timer.SetCountTime(m_player->GetAppealTime());
		m_timer.Reset();
	}
	void PlayerModel::GoalBehavior() {
		auto drawComp = GetComponent<PNTBoneModelDraw>();
		drawComp->UpdateAnimation(App::GetApp()->GetElapsedTime());
		if (m_timer.Count()) {
			m_StateMachine->ChangeState(PlayerModelRun::Instance());
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
	//���s��
	shared_ptr<PlayerModelRun> PlayerModelRun::Instance() {
		static shared_ptr<PlayerModelRun> instance(new PlayerModelRun);
		return instance;
	}
	void PlayerModelRun::Enter(const shared_ptr<PlayerModel>& Obj) {
		Obj->RunInit();
	}
	void PlayerModelRun::Execute(const shared_ptr<PlayerModel>& Obj) {
		Obj->RunBehavior();
	}
	void PlayerModelRun::Exit(const shared_ptr<PlayerModel>& Obj) {}
	//�_���[�W��
	shared_ptr<PlayerModelDamage> PlayerModelDamage::Instance() {
		static shared_ptr<PlayerModelDamage> instance(new PlayerModelDamage);
		return instance;
	}
	void PlayerModelDamage::Enter(const shared_ptr<PlayerModel>& Obj) {
		Obj->DamageInit();
	}
	void PlayerModelDamage::Execute(const shared_ptr<PlayerModel>& Obj) {
		Obj->DamageBehavior();
	}
	void PlayerModelDamage::Exit(const shared_ptr<PlayerModel>& Obj) {}
	//�ʏ펞
	shared_ptr<PlayerModelNormal> PlayerModelNormal::Instance() {
		static shared_ptr<PlayerModelNormal> instance(new PlayerModelNormal);
		return instance;
	}
	void PlayerModelNormal::Enter(const shared_ptr<PlayerModel>& Obj) {
		Obj->NormalInit();
		m_timer.SetCountTime(m_motionOffset);
		m_timer.Reset();
	}
	void PlayerModelNormal::Execute(const shared_ptr<PlayerModel>& Obj) {
		Obj->NormalBehavior();
		if (m_timer.Count()) {
			Obj->GetStateMachine()->ChangeState(PlayerModelGoal::Instance());
		}
	}
	void PlayerModelNormal::Exit(const shared_ptr<PlayerModel>& Obj) {}
	//�S�[����
	shared_ptr<PlayerModelGoal> PlayerModelGoal::Instance() {
		static shared_ptr<PlayerModelGoal> instance(new PlayerModelGoal);
		return instance;
	}
	void PlayerModelGoal::Enter(const shared_ptr<PlayerModel>& Obj) {
		Obj->GoalInit();
	}
	void PlayerModelGoal::Execute(const shared_ptr<PlayerModel>& Obj) {
		Obj->GoalBehavior();
	}
	void PlayerModelGoal::Exit(const shared_ptr<PlayerModel>& Obj) {}
}