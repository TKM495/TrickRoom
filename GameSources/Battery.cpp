#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void battery::OnCreate()
	{
		auto drawComp = AddComponent<BcPNTStaticDraw>(); // �h���[(�`��)�R���|�[�l���g��ǉ�
		drawComp->SetMeshResource(L"DEFAULT_CUBE"); // �����ڂƂ��ă��b�V����ݒ�

		 //�f�o�b�O�p�̕������\�����邽�߂̃R���|�[�l���g��ǉ�
		auto ssComp = AddComponent<StringSprite>();
		ssComp->SetBackColor(Col4(0.0f, 0.0f, 0.0f, 0.5f)); // ������̕\���̈�̔w�i�F��ύX����
		ssComp->SetTextRect(Rect2D<float>(10, 10, 300 + 10, 200 + 10)); // ������\���̈�̃T�C�Y��ύX����
		ssComp->SetText(L"Hello world");

		auto transComp = GetComponent<Transform>(); // �g�����X�t�H�[��(�s��ϊ�)�R���|�[�l���g���擾
		transComp->SetRotation(0, XMConvertToRadians(0), 0);
	}

	void battery::OnUpdate()
	{
		auto& app = App::GetApp();

		float delta = app->GetElapsedTime();

		auto device = app->GetInputDevice();
		const auto& pad = device.GetControlerVec()[0]; // 0�Ԗڂ̃p�b�h���擾

		auto transComp = GetComponent<Transform>(); // �g�����X�t�H�[��(�s��ϊ�)�R���|�[�l���g���擾
		auto pos = transComp->GetPosition(); // ���݂̈ʒu���W���擾
		auto quat = transComp->GetQuaternion(); // ��]���擾����Ƃ��̓N�H�[�^�j�I����p����
		auto rot = quat.toRotVec(); // �����Ƃ̉�]�ɕϊ�����

		// �f�o�b�O�p������ɏo�͓��e���\�z����
		wss.str(L"");
		wss << XMConvertToDegrees(rot.x) << ", "
			<< XMConvertToDegrees(rot.y) << ", "
			<< XMConvertToDegrees(rot.z) << std::endl; // �����Ƃ̉�]�p��\��
		wss << L"Bullet count : " << Bullet::getCount();

		// �擾�����ʒu���W���X�e�B�b�N�̌X�������ƂɍX�V����
		float h = pad.fThumbLX;
		float v = pad.fThumbLY;
		pos += Vec3(h, 0.0f, v) * 2.0f * delta;

		// ���[�̈ړ�����
		if (pos.x - 0.5f < -5.0f + 1.0f)
		{
			pos.x = -5.0f + 1.0f + 0.5f;
		}

		// �E�[�̈ړ�����
		if (pos.x + 0.5f > +5.0f - 1.0f)
		{
			pos.x = +5.0f - 1.0f - 0.5f;
		}

		// �O�[�̈ړ�����
		if (pos.z + 0.5f > +5.0f - 1.0f)
		{
			pos.z = +5.0f - 1.0f - 0.5f;
		}

		// ��[�̈ړ�����
		if (pos.z - 0.5f < -5.0f + 1.0f)
		{
			pos.z = -5.0f + 1.0f + 0.5f;
		}

		// �X�e�B�b�N�̓|��Ă���������p�x�ɒ���
		if (v != 0 && h != 0) // �X�e�B�b�N���|��Ă�����E�E
		{
			rot.y = atan2f(-v, h) + XM_PIDIV2; // �X�e�B�b�N�̌����ŏ㏑���i�i�s�������[���x�ɂ��邽�߂ɁA�X�O�x��]������j
		}

		// A�{�^���������ꂽ��A�e�𔭎˂���
		delay += delta;
		if (delay > 0.5f)
		{
			ShotBullet();
			delay = 0;
		}

		transComp->SetRotation(0, rot.y, 0);
		transComp->SetPosition(pos); // �X�V�������W��Transform�ɐݒ肷��
	}

	void battery::OnUpdate2()
	{
		auto ssComp = GetComponent<StringSprite>();
		ssComp->SetText(wss.str());
	}

	// �e�𔭎˂���֐�
	void battery::ShotBullet()
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
