/*!
@file Player.cpp
@brief
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	Player::Player(const std::shared_ptr<Stage>& stage,
		const wstring& line)
			: StageObject(stage),
		m_moveSpeed(3.5f),
		m_HP(5),
		m_crystal(0),
		m_count(0),
		m_RespawnTime(2),
		bRespawn(false)
	{
		//トークン（カラム）の配列
		vector<wstring> tokens;
		Util::WStrToTokenVector(tokens, line, L',');
		//各トークン（カラム）をスケール、回転、位置に読み込む
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
		m_respawnPos = m_position;

	}

	void Player::OnCreate()
	{
		StageObject::OnCreate();
		GetStage()->SetSharedGameObject(L"Player", GetThis<Player>());

		auto drawComp = AddComponent<BcPNTStaticDraw>();
		 drawComp->SetMeshResource(L"DEFAULT_CUBE");

		//auto ssComp = AddComponent<StringSprite>();
		//ssComp->SetBackColor(Col4(0.0f, 0.0f, 0.0f, 0.5f));
		//ssComp->SetTextRect(Rect2D<float>(10, 10, 300 + 10, 200 + 10));
		//ssComp->SetText(L"HP 3\nCRYSTAL 10");

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
		cameraDir.y = 0.0f;
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
		if (!bRespawn)
		{
			Move();
		}

		else
		{
			Respawn();
		}

		//m_InputHandler.PushHandle(GetThis<Player>());

	}

	//void Player::OnPushA()
	//{
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

	void Player::Move()
	{
		auto stage = GetStage();

		auto camera = stage->GetView()->GetTargetCamera();
		auto mainCamera = dynamic_pointer_cast<MainCamera>(camera);

		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();
		auto cameraDir = pos - camera->GetEye();
		cameraDir.y = 0.0f;

		SetSpeed();

		pos += m_Speed;

		transComp->SetPosition(pos);

		if (m_Speed.length() > 0.0f)
		{
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(m_Speed, 1.0f);
		}

	}

	void Player::Respawn()
	{
		auto& app = App::GetApp();
		float ElapsedTime = app->GetElapsedTime();

		m_count += ElapsedTime;

		if (m_count > m_RespawnTime)
		{
			SetDrawActive(true);
			bRespawn = false;

			auto transComponent = GetComponent<Transform>();
			transComponent->SetPosition(m_respawnPos);

			m_count = 0;
		}
	}
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
		if (!bRespawn)
		{
			auto bDamegeTag = other->FindTag(L"damage");

			if (bDamegeTag)
			{
				m_HP += -1;
				bRespawn = true;

				SetDrawActive(false);
			}

		}
	}

}
//end basecross

