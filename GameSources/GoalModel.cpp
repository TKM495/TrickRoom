#include "stdafx.h"
#include "Project.h"

namespace basecross {
	GoalModel::GoalModel(const std::shared_ptr<Stage>& stage,
		ObjectParam param)
		: GameObject(stage), m_param(param), m_bOpen(false), m_bOnce(false)
	{}

	void GoalModel::OnCreate()
	{
		GetStage()->SetSharedGameObject(L"GoalModel", GetThis<GoalModel>());
		auto transComp = GetComponent<Transform>();
		m_param.rotation += Utility::ConvertDegVecToRadVec(Vec3(0.0f, 180.0f, 0.0f));
		transComp->SetPosition(m_param.position);
		transComp->SetScale(Vec3(0.6f));
		transComp->SetRotation(m_param.rotation);

		//影はないほうがよかったのでコメントアウト
		//auto shadow = AddComponent<Shadowmap>();
		//shadow->SetMeshResource(L"Goal");

		auto drawComp = AddComponent<PNTBoneModelDraw>();
		drawComp->SetMeshResource(L"Goal");
		//本来は0～30だが扉がめり込むステージがあったため制限した
		//追記(05/24):扉を奥側に空けるようにしたので制限を解除
		drawComp->AddAnimation(L"Open", 0, 30, false, 30.0f);
		drawComp->AddAnimation(L"Close", 30, 60, false, 60.0f);

		ObjectParam param = {
			m_param.position + Vec3(0.0f,1.2f,0.0f),
			Vec3(2.5f,2.4f,1.0f),
			m_param.rotation
		};
		GetStage()->AddGameObject<StaticPlatePolygon>(L"White1x1", param);
		SetDrawLayer(1);
		//ステートマシンの構築
		m_stateMachine.reset(new StateMachine<GoalModel>(GetThis<GoalModel>()));
		//初期ステートの設定
		m_stateMachine->ChangeState(GoalModelStay::Instance());
	}

	void GoalModel::OnUpdate() {
		m_stateMachine->Update();
	}

	void GoalModel::OpenBehavior() {
		//auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		//auto playerPos = player->GetComponent<Transform>()->GetPosition();
		//auto drawComp = GetComponent<PNTBoneModelDraw>();
		//float delta = App::GetApp()->GetElapsedTime();

		//auto dir = playerPos - m_param.position;
		//if (dir.length() < 3.0f) {
		//	drawComp->UpdateAnimation(delta);
		//	m_bOpen = true;
		//}

		//if (m_bOpen && !m_bOnce) {
		//	auto audio = App::GetApp()->GetXAudio2Manager();
		//	audio->Start(L"DoorOpenSE", 0, 0.1f);
		//	m_bOnce = true;
		//}
		auto drawComp = GetComponent<PNTBoneModelDraw>();
		float delta = App::GetApp()->GetElapsedTime();
		drawComp->UpdateAnimation(delta);
		if (drawComp->IsTargetAnimeEnd()) {
			m_stateMachine->ChangeState(GoalModelStay::Instance());
		}
	}

	shared_ptr<GoalModelOpen> GoalModelOpen::Instance() {
		static shared_ptr<GoalModelOpen> instance(new GoalModelOpen);
		return instance;
	}
	void GoalModelOpen::Enter(const shared_ptr<GoalModel>& Obj) {
		auto drawComp = Obj->GetComponent<PNTBoneModelDraw>();
		drawComp->ChangeCurrentAnimation(L"Open");
		auto audio = App::GetApp()->GetXAudio2Manager();
		audio->Start(L"DoorOpenSE", 0, 0.1f);
	}
	void GoalModelOpen::Execute(const shared_ptr<GoalModel>& Obj) {
		Obj->OpenBehavior();
	}
	void GoalModelOpen::Exit(const shared_ptr<GoalModel>& Obj) {}

	shared_ptr<GoalModelStay> GoalModelStay::Instance() {
		static shared_ptr<GoalModelStay> instance(new GoalModelStay);
		return instance;
	}
	void GoalModelStay::Enter(const shared_ptr<GoalModel>& Obj) {}
	void GoalModelStay::Execute(const shared_ptr<GoalModel>& Obj) {}
	void GoalModelStay::Exit(const shared_ptr<GoalModel>& Obj) {}
}
