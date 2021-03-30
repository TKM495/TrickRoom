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
		m_moveSpeed(6), m_HP(5), m_crystal(0),
		bMutekiFlg(false), m_Mcount(0), m_MTime(2)
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
		//m_respawnPos = m_position;

	}

	void Player::OnCreate()
	{
		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		transComp->SetScale(m_scale);
		transComp->SetRotation(m_rotation);

		GetStage()->SetSharedGameObject(L"Player", GetThis<Player>());

		auto drawComp = AddComponent<BcPNTStaticDraw>();
		 drawComp->SetMeshResource(L"DEFAULT_CUBE");

		 AddTag(L"Player");

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
		auto stage = GetStage();

		auto camera = stage->GetView()->GetTargetCamera();
		auto mainCamera = dynamic_pointer_cast<MainCamera>(camera);

		if (mainCamera->GetbLeapFlg())
		{
			return;
		}

		Move();

		if (bMutekiFlg)
		{
			Muteki();
		}

		if (m_HP <= 0) {
			SetDrawActive(false);
			SetUpdateActive(false);
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

	void Player::Muteki()
	{
		auto& app = App::GetApp();
		float ElapsedTime = app->GetElapsedTime();

		m_Mcount += ElapsedTime;

		if (m_Mcount > m_MTime)
		{
			SetDrawActive(true);
			bMutekiFlg = false;
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
		if (!bMutekiFlg)
		{
			auto bDamegeTag = other->FindTag(L"damage");

			if (bDamegeTag)
			{
				m_HP += -1;
				bMutekiFlg = true;
				auto ColComp = GetComponent<Collision>();
			}
		}
		if (other->FindTag(L"Crystal")) {
			m_crystal++;
			other->SetDrawActive(false);
			other->SetUpdateActive(false);
			other->AddNumTag(-1);
		}
	}
}
//end basecross

