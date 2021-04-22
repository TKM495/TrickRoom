/*!
@file EnemyArt.cpp
@brief �g���b�N�A�[�g�̓G�N���X����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	EnemyArt::EnemyArt(const shared_ptr<Stage>& stage,
		const wstring& line)
		:TrickArtBaseOld(stage)
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
		m_activeState = tokens[10] == L"Right" ? state::Right : state::Left;
		m_texStr = tokens[11].c_str();

		m_behavior = tokens[12];
		m_cycle = (float)_wtof(tokens[13].c_str());
		m_speed = (float)_wtof(tokens[14].c_str());
		m_offset = (float)_wtof(tokens[15].c_str());
	}

	void EnemyArt::OnCreate() {
		//�F�̃f�[�^(R,G,B,A)
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		//���_�̃f�[�^ (�ԍ��͍��ォ��E���܂�)
		m_vertices = {
			{Vec3(-1.0f, 0.0f,+1.0f),color,Vec2(0.0f,0.0f)}, //0
			{Vec3(+1.0f, 0.0f,+1.0f),color,Vec2(1.0f,0.0f)}, //1
			{Vec3(-1.0f, 0.0f,-1.0f),color,Vec2(0.0f,1.0f)}, //2
			{Vec3(+1.0f, 0.0f,-1.0f),color,Vec2(1.0f,1.0f)}  //3
		};
		//���_�C���f�b�N�X(���_���Ȃ��鏇��)
		m_indices = {
			0, 1, 2, //��̎O�p�`
			2, 1, 3  //���̎O�p�`
		};

		TrickArtBaseOld::OnCreate();

		auto obbComp = AddComponent<CollisionObb>();
		//obbComp->SetFixed(true);
		obbComp->SetAfterCollision(AfterCollision::None);

		auto scene = App::GetApp()->GetScene<Scene>();
		if (scene->GetDebugState() == DebugState::Debug) {
			obbComp->SetDrawActive(true);
		}
		//obbComp->SetAfterCollision(AfterCollision::None);

		if (m_behavior == L"SinCurve") {
			GetBehavior<SinCurve>()->SetOffset(m_offset);
		}
		else if (m_behavior == L"SquareMove") {
			GetBehavior<SquareMove>()->SetSpeed(m_speed);
		}
		else {

		}


		//�����蔻��̐؂�ւ��Ń_���[�W�̔�����s������
		//��ɂ��̃^�O������
		AddTag(L"damage");
	}

	void EnemyArt::OnUpdate() {
		auto camera = dynamic_pointer_cast<MainCamera>(OnGetDrawCamera());
		state nowState = camera->GetCamState();
		if (nowState == m_activeState) {
			GetComponent<CollisionObb>()->SetUpdateActive(true);
		}
		else {
			GetComponent<CollisionObb>()->SetUpdateActive(false);
		}

		auto state = dynamic_pointer_cast<GameStage>(GetStage())->GetState();
		switch (state)
		{
		case basecross::GameStage::GameState::PLAYING:
			if (camera->GetbLeapFlg()) {
				return;
			}

			if (m_behavior == L"SinCurve") {
				GetBehavior<SinCurve>()->Excute(m_cycle, m_speed);
			}
			else if (m_behavior == L"SquareMove") {
				GetBehavior<SquareMove>()->Excute();
			}
			else {

			}
			break;
		case basecross::GameStage::GameState::PAUSE:
			break;
		}

	}

	void EnemyArt::OnCollisionEnter(shared_ptr<GameObject>& other) {
		//���������damage�̃^�O������΂����̂ł��̏����̓R�����g�A�E�g
		//auto player = dynamic_pointer_cast<Player>(other);
		//if (player) {
		//	return;
		//}

		//�I�u�W�F�N�g�������Ă������Ǝv�������A�O�̂���
		if (other->FindTag(L"damage")) {
			SetDrawActive(false);
			SetUpdateActive(false);
			AddNumTag(-1);
		}
	}
}
//end basecross