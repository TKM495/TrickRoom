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
		transComp->SetPosition(pos); // �X�V�������W��Transform�ɐݒ�

	}

}
//end basecross

