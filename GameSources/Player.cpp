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
		m_moveSpeed(6), m_HP(3), m_Rcrystal(0),m_Bcrystal(0),
		bMutekiFlg(false), m_Mcount(0), m_MTime(2),
		m_DrawCount(0), m_BlinkMask(8)
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
		m_position.x += dynamic_pointer_cast<GameStage>(GetStage())->GetStartOffset();

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		transComp->SetScale(m_scale);
		transComp->SetRotation(m_rotation);

		GetStage()->SetSharedGameObject(L"Player", GetThis<Player>());

		auto drawComp = AddComponent<BcPNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");

		auto shadow = AddComponent<Shadowmap>();
		shadow->SetMeshResource(L"DEFAULT_CUBE");

		 AddTag(L"Player");

		AddComponent<Gravity>();
		AddComponent<CollisionObb>();
	}

	Vec3 Player::MoveVec()
	{
		auto stage = dynamic_pointer_cast<GameStage>(GetStage());

		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();

		const auto& app = App::GetApp();
		float ElapsedTime = app->GetElapsedTime();
		const auto& cntlPad = app->GetInputDevice().GetControlerVec()[0];

		float fThumbLY = cntlPad.fThumbLY;

		Vec3 moveVec;
		switch (stage->GetState())
		{
		case GameStage::GameState::PLAYING:
			moveVec = Vec3(-1.0f, 0.0f, fThumbLY);
			break;
		case GameStage::GameState::PAUSE:
			moveVec = Vec3(0.0f);
			break;
		default:
			moveVec = Vec3(-1.0f, 0.0f, 0.0f);
			break;
		}

		return moveVec * m_moveSpeed * ElapsedTime;


	}

	void Player::OnUpdate()
	{
		auto stage = GetStage();
		auto pursuer = stage->GetSharedGameObject<Pursuer>(L"Pursuer");

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
			Draw();
		}

		auto pursuerPos = pursuer->GetPos();
		auto myPos = GetComponent<Transform>()->GetPosition();
		auto dir = pursuerPos.x- myPos.x;

		//HPが0になったらゲームオーバー
		if (m_HP <= 0|| dir < 0.1f) {
			ToGameOver();
		}

		if (myPos.x > 100.0f || myPos.x < -100.0f) {
			GetComponent<Gravity>()->SetUpdateActive(false);
		}
		else {
			GetComponent<Gravity>()->SetUpdateActive(true);
		}
	}

	void Player::Move()
	{
		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetWorldPosition();

		pos += MoveVec();

		transComp->SetWorldPosition(pos);

		if (MoveVec().length() > 0.0f)
		{
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(MoveVec(), 1.0f);
		}

		SetDrawActive(true);
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

	void Player::Draw()
	{
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


	void Player::SetHP(int HP)
	{
		m_HP = HP;
	}

	int Player::GetHP() {
		return m_HP;
	}

	int Player::GetCrystal()
	{
		return m_Rcrystal + m_Bcrystal;
	}

	void Player::ToGameOver() {
		SetDrawActive(false);
		SetUpdateActive(false);

		auto nowPos = GetComponent<Transform>()->GetPosition();

		ScoreData data{
			GameStage::GameState::GAMEOVER,
			0, //ゲームオーバー時はHPは0
			m_Rcrystal,
			m_Bcrystal,
			(int)Util::Round((double)m_position.x - nowPos.x,0)
		};
		App::GetApp()->GetScene<Scene>()->SetScoreData(data);
		//この時点でstateはGameOverになっている
		dynamic_pointer_cast<GameStage>(GetStage())->SetState(data.state);
	}

	void Player::ToClear() {
		SetDrawActive(false);
		SetUpdateActive(false);
		auto nowPos = GetComponent<Transform>()->GetPosition();

		ScoreData data{
			GameStage::GameState::CLEAR,
			m_HP,
			m_Rcrystal,
			m_Bcrystal,
			(int)Util::Round((double)m_position.x - nowPos.x,0)
		};
		App::GetApp()->GetScene<Scene>()->SetScoreData(data);
		//この時点でstateはClearになっている
		dynamic_pointer_cast<GameStage>(GetStage())->SetState(data.state);
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
				auto audio = App::GetApp()->GetXAudio2Manager();
				audio->Start(L"DamageSE", 0, 0.1f);
				auto ColComp = GetComponent<Collision>();

				ColComp->AddExcludeCollisionTag(L"damege");

				//SetDrawActive(false);

				auto effect = GetStage()->GetSharedGameObject<Effect>(L"Effect");
				effect->InsertEffect(other->GetComponent<Transform>()->GetPosition());
			}
		}

		auto bCrystalTag = other->FindTag(L"Crystal");
		if (bCrystalTag)
		{
			//auto ColComp = GetComponent<Collision>();

			//ColComp->AddExcludeCollisionTag(L"crystal");

			auto effect = GetStage()->GetSharedGameObject<Effect>(L"C_Effect");
			effect->CrystalEffect(other->GetComponent<Transform>()->GetPosition());
			if (other->FindTag(L"Red")) {
				m_Rcrystal++;
			}
			else if (other->FindTag(L"Blue")) {
				m_Bcrystal++;
			}
			else {
				throw BaseException(
					L"タグが見つかりません",
					L"FindTag() != Red or Blue",
					L"Player::OnCollisionEnter()"
				);
			}
			other->SetDrawActive(false);
			other->SetUpdateActive(false);
			other->AddNumTag(-1);

			//SE
			auto audio = App::GetApp()->GetXAudio2Manager();
			audio->Start(L"CrystalSE", 0, 0.1f);
		}

		if (other->FindTag(L"Goal")) {
			ToClear();
		}
	}
}
//end basecross

