/*!
@file Enemy.cpp
@brief �G����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Enemy::Enemy(const shared_ptr<Stage>& stage,
		const wstring& line)
		:StageObject(stage)
	{
		//�g�[�N���i�J�����j�̔z��
		vector<wstring> tokens;
		Util::WStrToTokenVector(tokens, line, L',');
		//�e�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
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

		m_behavior = tokens[10];
		m_cycle = (float)_wtof(tokens[11].c_str());
		m_speed = (float)_wtof(tokens[12].c_str());
		m_offset = (float)_wtof(tokens[13].c_str());
	}
	void Enemy::OnCreate() {
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"Enemy");

		auto collComp = AddComponent<CollisionSphere>();
		collComp->SetAfterCollision(AfterCollision::None);

		auto scene = App::GetApp()->GetScene<Scene>();
		if (scene->GetDebugState() == DebugState::Debug) {
			collComp->SetDrawActive(true);
		}

		StageObject::OnCreate();

		if (m_behavior == L"SinCurve") {
			GetBehavior<SinCurve>()->SetOffset(m_offset);
		}
		else {

		}


		AddTag(L"damage");
	}

	void Enemy::OnUpdate() {
		auto state = dynamic_pointer_cast<GameStage>(GetStage())->GetState();
		auto camera = dynamic_pointer_cast<MainCamera>(GetStage()->GetView()->GetTargetCamera());
		switch (state)
		{
		case basecross::GameStage::GameState::PLAYING:
			if (camera->GetbLeapFlg()) {
				return;
			}

			if (m_behavior == L"SinCurve") {
				GetBehavior<SinCurve>()->Excute(m_cycle, m_speed);
			}
			else {

			}
			break;
		case basecross::GameStage::GameState::PAUSE:
			break;
		}
	}

	void Enemy::OnCollisionEnter(shared_ptr<GameObject>& other) {
		//判定条件がdamageのタグがあればいいのでこの処理はコメントアウト
		//auto player = dynamic_pointer_cast<Player>(other);
		//if (player) {
		//	return;
		//}

		//オブジェクトを消してもいいと思ったが、念のため
		if (other->FindTag(L"damage")) {
			SetDrawActive(false);
			SetUpdateActive(false);
			AddNumTag(-1);
		}
	}
}
//end basecross