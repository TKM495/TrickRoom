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

		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();

		const auto& app = App::GetApp();
		float ElapsedTime = app->GetElapsedTime();
		const auto& cntlPad = app->GetInputDevice().GetControlerVec()[0];

		float fThumbLY = cntlPad.fThumbLY;

		Vec3 moveVec = Vec3(-1.0f, 0.0f, fThumbLY);
		return moveVec * m_moveSpeed * ElapsedTime;


	}

	void Player::OnUpdate()
	{
		Move();

		auto stage = GetStage();

		auto camera = stage->GetView()->GetTargetCamera();
		auto mainCamera = dynamic_pointer_cast<MainCamera>(camera);

		if (mainCamera->GetbLeapFlg())
		{
			return;
		}

		if (!bMutekiFlg)
		{
			Move();
		}

		else
		{
			Muteki();
		}
	}

	void Player::Move()
	{
		auto stage = GetStage();

		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetWorldPosition();

		pos += MoveVec();

		transComp->SetWorldPosition(pos);

		if (MoveVec().length() > 0.0f)
		{
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(MoveVec(), 1.0f);
		}

	}

	//void Player::Respawn()
	//{
	//	auto& app = App::GetApp();
	//	float ElapsedTime = app->GetElapsedTime();

	//	m_count += ElapsedTime;

	//	if (m_count > m_RespawnTime)
	//	{
	//		SetDrawActive(true);
	//		bRespawn = false;

	//		auto transComponent = GetComponent<Transform>();
	//		transComponent->SetPosition(5.0f, 0.0f, 0.0f);


	//		m_count = 0;
	//	}
	//}

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
	void Player::OnCollisionEnter(std::shared_ptr<GameObject>& other)
	{
		//if (!bRespawn)
		//{

		if (!bMutekiFlg)
		{
			auto bDamegeTag = other->FindTag(L"damege");


			if (bDamegeTag)
			{
				m_HP += -1;

				//bRespawn = true;
				bMutekiFlg = true;
				auto ColComp = GetComponent<Collision>();

				ColComp->AddExcludeCollisionTag(L"damege");

				SetDrawActive(false);

				auto effect = GetStage()->GetSharedGameObject<Effect>(L"Effect");
				effect->InsertEffect(other->GetComponent<Transform>()->GetPosition());

			}

		}
		//}

	}

}
//end basecross

