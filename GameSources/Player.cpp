/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void Player::OnCreate()
	{
		auto drawComp = AddComponent<BcPNTStaticDraw>();
		 drawComp->SetMeshResource(L"DEFAULT_CUBE");

		// �f�o�b�O�p�̕������\�����邽�߂̃R���|�[�l���g��ǉ�
		auto ssComp = AddComponent<StringSprite>();
		ssComp->SetBackColor(Col4(0.0f, 0.0f, 0.0f, 0.5f)); // ������̕\���̈�̔w�i�F��ύX����
		ssComp->SetTextRect(Rect2D<float>(10, 10, 300 + 10, 200 + 10)); // ������\���̈�̃T�C�Y��ύX����
		ssComp->SetText(L"HP 3\nCRYSTAL 10");



		auto transComp = GetComponent<Transform>(); // �g�����X�t�H�[��(�s��ϊ�)�R���|�[�l���g���擾
		transComp->SetRotation(0, XMConvertToRadians(0), 0);


		AddComponent<Gravity>();
		AddComponent<CollisionObb>();
	}

	void Player::SetSpeed()
	{
		auto& app = App::GetApp();
		float ElapsedTime = app->GetElapsedTime();
		auto cntlPad = app->GetInputDevice().GetControlerVec();//�R���g���[���[�̎擾

		float fThumbLY = 0.0f;
		float fThumbLX = 0.0f;
		if (cntlPad[0].bConnected)
		{
			fThumbLY = cntlPad[0].fThumbLY;
			fThumbLX = cntlPad[0].fThumbLX;
		}

		if (fThumbLX != 0 || fThumbLY != 0)
		{
			//�R���g���[���̌���
			float moveX = fThumbLX;
			float moveZ = fThumbLY;
			Vec2 moveVec(moveZ, moveX);
			float moveSize = moveVec.length();
			moveSize *= ElapsedTime * 5.0f;

			////Player�̌���
			//float MoveDirectionX = fThumbLX;
			//float MoveDirectionY = fThumbLY;

			//auto transComp = GetComponent<Transform>();
			//auto quat = transComp->GetQuaternion();
			//auto rot = quat.toRotVec(); //�����Ƃ̉�]�ɂ���

			//rot.y = atan2f(-MoveDirectionY, MoveDirectionX) + XM_PIDIV2;
			//transComp->SetRotation(0, rot.y, 0);

			//�p�x
			float cntlAngle = atan2(moveZ, moveX);
			//�x�N�g���쐬
			m_Speed = Vec3(cos(cntlAngle), 0, sin(cntlAngle));
			//���K������
			m_Speed.normalize();
			//�ړ��T�C�Y��ݒ�
			m_Speed *= moveSize;

			m_Speed.y = 0;
		}

		else
		{
			m_Speed = Vec3(0.0f);
		}

	}

	void Player::OnUpdate()
	{
		SetSpeed();

		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();
		pos += m_Speed;

		auto stage = GetStage(); // �X�e�[�W���擾

		transComp->SetPosition(pos); // �X�V�������W��Transform�ɐݒ�

		//Player�̌���
		if (m_Speed.length() > 0.0f)
		{
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(m_Speed, 1.0f);
		}

		//m_InputHandler.PushHandle(GetThis<Player>());

	}

	//void Player::OnPushA()
	//{


	//	//SetGravityVerocity���擾���āASetGravityVerocity��Speed��0�ɂȂ�����n�ʂƐڐG���Ă���ƌ��Ȃ��āA�t���O��|��
	//	if (bJump == false)
	//	{
	//		bJump = true;
	//		auto GravityComp = GetComponent<Gravity>();
	//		GravityComp->SetGravityVerocity(Vec3(0, 5, 0));

	//	}

	//	if ()
	//	{
	//		auto GravityComp = GetComponent<Gravity>();
	//		GravityComp->GetGravityVelocity();

	//	}

	//}


	void Player::SetHP(int HP)
	{
		m_HP = HP;
	}

	int Player::GetHP(){
		return m_HP;
	}

	float Player::GetCrystal()
	{
		return m_crystal;
	}


}
//end basecross

