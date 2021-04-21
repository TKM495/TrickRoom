/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Player::OnCreate()
	{
		auto drawComp = AddComponent<BcPNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");

		auto transComponent = GetComponent<Transform>();
		transComponent->SetPosition(5.0f, 0.0f, 0.0f);
		transComponent->SetScale(0.5, 1.0, 0.5);

		auto ssComp = AddComponent<StringSprite>();
		ssComp->SetBackColor(Col4(0.0f, 0.0f, 0.0f, 0.5f));
		ssComp->SetTextRect(Rect2D<float>(10, 10, 300 + 10, 200 + 10));
		ssComp->SetText(L"HP 3\nCRYSTAL 10");



		auto transComp = GetComponent<Transform>();
		transComp->SetRotation(0, XMConvertToRadians(0), 0);


		AddComponent<Gravity>();
		AddComponent<CollisionObb>();
	}

	Vec3 Player::MoveVec()
	{
		auto stage = GetStage();

		auto camera = stage->GetView()->GetTargetCamera();

		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();

		auto cameraDir = pos - camera->GetEye();
		cameraDir.y = 0.0f;
		cameraDir.normalize();

		const auto& app = App::GetApp();
		float ElapsedTime = app->GetElapsedTime();
		const auto& cntlPad = app->GetInputDevice().GetControlerVec()[0];


		float fThumbLY = 0.0f;
		float fThumbLX = 0.0f;
		if (cntlPad.bConnected)
		{
			fThumbLY = cntlPad.fThumbLY;
			fThumbLX = cntlPad.fThumbLX;
		}

		if (fThumbLX != 0 || fThumbLY != 0)
		{

			Vec3 Horizontal = cameraDir;
			Vec3 Vertical(Horizontal.z, 0, -Horizontal.x);

			Vec3 moveH = Vec3(Horizontal * fThumbLY);
			Vec3 moveV = Vec3(Vertical * fThumbLX);
			Vec3 moveVec = moveH + moveV;
			return moveVec * m_moveSpeed * ElapsedTime;
		}

		else
		{
			return Vec3(0.0f);
		}

	}

	void Player::OnUpdate()
	{

		auto stage = GetStage();

		auto camera = stage->GetView()->GetTargetCamera();
		auto mainCamera = dynamic_pointer_cast<MainCamera>(camera);

		if (mainCamera->GetbLeapFlg())
		{
			return;
		}

		if (!bRespawn)
		{
			Move();
			if (bDotFlg)
			{
				Draw();
				Muteki();
			}
		}

		else
		{
			Respawn();
		}


	}

	void Player::Move()
	{
		auto stage = GetStage();

		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();

		const auto& app = App::GetApp();
		float ElapsedTime = app->GetElapsedTime();

		pos += MoveVec();
		m_count += ElapsedTime;

		transComp->SetPosition(pos);

		if (MoveVec().length() > 0.0f)
		{
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(MoveVec(), rotationSpeed);
		}

		//SetDrawActive(true);
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

			bDotFlg = true;

			auto transComponent = GetComponent<Transform>();
			transComponent->SetPosition(3.0f, 0.0f, 0.0f);

			m_count = 0;
		}

	}

	//点滅
	void Player::Draw()
	{
		auto& app = App::GetApp();
		float ElapsedTime = app->GetElapsedTime();

		m_DotCount += ElapsedTime;
		if (m_DotCount > m_DotMaxCount)
		{
			bDotFlg = false;
		}

		if (m_DrawCount & m_BlinkMask)
		{
			SetDrawActive(true);
		}


		else
		{
			SetDrawActive(false);
		}

		++m_DrawCount;

	}

	void Player::Muteki()
	{
		auto& app = App::GetApp();
		float ElapsedTime = app->GetElapsedTime();

		auto ColComp = GetComponent<Collision>();


		m_Mcount += ElapsedTime;

		if (m_Mcount > m_MTime)
		{
			SetDrawActive(true);
			bMutekiFlg = false;
			ColComp->RemoveExcludeCollisionTag(L"damege");

			m_Mcount = 0;
		}

	}

	void Player::SetHP(int HP)
	{
		m_HP = HP;
	}

	int Player::GetHP() {
		return m_HP;
	}

	int Player::GetCrystal()
	{
		return m_crystal;
	}

	//衝突判定
	void Player::OnCollisionExcute(std::shared_ptr<GameObject>& other)
	{
		if (!bRespawn && !bMutekiFlg)
		{
			auto bDamegeTag = other->FindTag(L"damege");

			auto bCrystalTag = other->FindTag(L"crystal");

			if (bDamegeTag)
			{
				m_HP += -1;

				bRespawn = true;
				SetDrawActive(false);
				bMutekiFlg = true;

				m_DotCount = 0;

				auto effect = GetStage()->GetSharedGameObject<Effect>(L"Effect");
				effect->InsertEffect(other->GetComponent<Transform>()->GetPosition());
			}

			if (bCrystalTag)
			{
				//auto ColComp = GetComponent<Collision>();

				//ColComp->AddExcludeCollisionTag(L"crystal");

				auto effect = GetStage()->GetSharedGameObject<Effect>(L"C_Effect");
				effect->CrystalEffect(other->GetComponent<Transform>()->GetPosition());
			}

		}

	}

}
//end basecross

