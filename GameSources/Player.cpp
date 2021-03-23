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

		auto ssComp = AddComponent<StringSprite>();
		ssComp->SetBackColor(Col4(0.0f, 0.0f, 0.0f, 0.5f));
		ssComp->SetTextRect(Rect2D<float>(10, 10, 300 + 10, 200 + 10));
		ssComp->SetText(L"HP 3\nCRYSTAL 10");



		auto transComp = GetComponent<Transform>();
		transComp->SetRotation(0, XMConvertToRadians(0), 0);


		AddComponent<Gravity>();
		AddComponent<CollisionObb>();
	}

	void Player::SetSpeed()
	{
		auto stage = GetStage();

		auto camera = stage->GetView()->GetTargetCamera();
		auto mainCamera = dynamic_pointer_cast<MainCamera>(camera);

		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();
		auto cameraDir = pos - camera->GetEye();
		cameraDir.y - 0.0f;
		cameraDir.normalize();

		auto& app = App::GetApp();
		float ElapsedTime = app->GetElapsedTime();
		auto cntlPad = app->GetInputDevice().GetControlerVec();

		float fThumbLY = 0.0f;
		float fThumbLX = 0.0f;
		if (cntlPad[0].bConnected)
		{
			fThumbLY = cntlPad[0].fThumbLY;
			fThumbLX = cntlPad[0].fThumbLX;
		}

		if (fThumbLX != 0 || fThumbLY != 0)
		{

			Vec3 Horizontal(cameraDir);
			Vec3 Vertical(Horizontal.z, 0, -Horizontal.x);

			Vec3 moveH = Vec3(Horizontal * fThumbLY);
			Vec3 moveV = Vec3(Vertical * fThumbLX);
			Vec3 moveVec = moveH + moveV;
			m_Speed = moveVec * m_moveSpeed * ElapsedTime;

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

	void Player::OnCollisionEnter(std::shared_ptr<GameObject>& other)
	{
		auto bDamegeTag = other->FindTag(L"damege");

		if (bDamegeTag)
		{
			m_HP += -1;

			auto transComponent = GetComponent<Transform>();
			transComponent->SetPosition(5.0f, 0.0f, 0.0f);
		}
	}

}
//end basecross

