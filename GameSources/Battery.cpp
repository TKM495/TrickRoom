#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Battery::Battery(const shared_ptr<Stage>& stage,
		const wstring& line)
		:StageObject(stage), delay(0.0f)
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
		interval = (float)_wtof(tokens[10].c_str());
	}

	void Battery::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>(); // �h���[(�`��)�R���|�[�l���g��ǉ�
		drawComp->SetMeshResource(L"DEFAULT_CUBE"); // �����ڂƂ��ă��b�V����ݒ�
		auto col = AddComponent<CollisionObb>();
		col->SetFixed(true);
		StageObject::OnCreate();
		AddTag(L"Battery");
	}

	void Battery::OnUpdate()
	{
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();
		auto state = dynamic_pointer_cast<GameStage>(GetStage())->GetState();
		switch (state)
		{
		default:
			delay += delta;
			break;
		case basecross::GameStage::GameState::PAUSE:
			break;
		}
		if (delay > interval)
		{
			ShotBullet();
			delay = 0;
		}
	}

	// �e�𔭎˂���֐�
	void Battery::ShotBullet()
	{
		// �v���C���[���g�̃g�����X�t�H�[�����擾����
		auto playerTrans = GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition();
		auto playerQuat = playerTrans->GetQuaternion();

		auto stage = GetStage(); // Player�I�u�W�F�N�g����������X�e�[�W���擾����
		auto bullet = stage->AddGameObject<Bullet>(); // ���̃X�e�[�W�ɒe��ǉ�����
		auto bulletTrans = bullet->GetComponent<Transform>();
		bulletTrans->SetPosition(playerPos); // �v���C���[�̍��W�ɍ��킹��
		bulletTrans->SetQuaternion(playerQuat); // �v���C���[�̕���(�p��)�ɍ��킹��
	}
}
