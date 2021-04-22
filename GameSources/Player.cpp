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
		m_moveSpeed(4), m_HP(3), m_Crystal(0),
		bMutekiFlg(false), m_Mcount(0), m_MTime(2),
		m_DrawCount(0), m_BlinkMask(8), rotationSpeed(0.2f),
		m_bExtrude(false), m_deltaExtrude(0.0f),
		bDotFlg(false), m_DotCount(0), m_DotMaxCount(2),
		m_count(0), m_RespawnTime(3), bRespawn(false)
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
		m_position.y = 0.25f;
		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		transComp->SetScale(Vec3(0.2f));
		transComp->SetRotation(m_rotation);

		GetStage()->SetSharedGameObject(L"Player", GetThis<Player>());

		auto drawComp = AddComponent<PNTStaticModelDraw>();
		drawComp->SetMultiMeshResource(L"PlayerModel");

		auto shadow = AddComponent<Shadowmap>();
		shadow->SetMultiMeshResource(L"PlayerModel");

		 AddTag(L"Player");

		AddComponent<Gravity>();
		AddComponent<CollisionObb>();
	}

	Vec3 Player::MoveVec()
	{
		auto stage = dynamic_pointer_cast<GameStage>(GetStage());

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
			switch (stage->GetState())
			{
			case GameStage::GameState::PLAYING:
				break;
			case GameStage::GameState::PAUSE:
				moveVec = Vec3(0.0f);
				break;
			default:
				moveVec = Vec3(0.0f, 0.0f, 0.0f);
				break;
			}
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

		if (m_bExtrude) {
			auto delta = App::GetApp()->GetElapsedTime();
			auto pos = GetComponent<Transform>()->GetPosition();
			pos.y = Lerp::CalculateLerp(m_startPos, m_startPos + m_dir, 0.0, 1.0f, m_deltaExtrude, Lerp::rate::Linear);
			GetComponent<Transform>()->SetPosition(pos);
			m_deltaExtrude += delta;
			if (m_deltaExtrude > 1.0f) {
				m_deltaExtrude = 0.0f;
				m_bExtrude = false;
			}
		}
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

		if (bMutekiFlg)
		{
			Respawn();
		}

		auto myPos = GetComponent<Transform>()->GetPosition();

		if (m_HP <= 1) {
			auto colorout = stage->GetSharedGameObject<ColorOut>(L"ColorOut");
			colorout->SetColor(Col4(1.0f, 0.0f, 0.0f, 1.0f));
			colorout->SetRange(0.25f, 0.0f);
			colorout->SetActive(true);
		}
	}

	void Player::Move()
	{
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
			//3Dモデルが逆になっているので一時的にこれ
			utilPtr->RotToHead(-MoveVec(), rotationSpeed);
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
		return m_Crystal;
	}

	void Player::ToClear() {
		SetDrawActive(false);
		SetUpdateActive(false);
		auto cam = dynamic_pointer_cast<MainCamera>(OnGetDrawCamera());
		ScoreData data{
			20.0f,		//タイム
			m_Crystal,	//クリスタル
			cam->GetCameraCount()
		};
		App::GetApp()->GetScene<Scene>()->SetScoreData(data);
		dynamic_pointer_cast<GameStage>(GetStage())->SetState(GameStage::GameState::CLEAR);
	}

	//衝突判定
	void Player::OnCollisionEnter(std::shared_ptr<GameObject>& other)
	{
		auto bCrystalTag = other->FindTag(L"Crystal");
		if (bCrystalTag)
		{
			//auto ColComp = GetComponent<Collision>();

			//ColComp->AddExcludeCollisionTag(L"crystal");

			auto effect = GetStage()->GetSharedGameObject<Effect>(L"C_Effect");
			effect->CrystalEffect(other->GetComponent<Transform>()->GetPosition());

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

		if (other->FindTag(L"TrickArtObj")) {
			auto camera = GetStage()->GetView()->GetTargetCamera();
			auto mainCamera = dynamic_pointer_cast<MainCamera>(camera);
			if (!mainCamera->GetbLeapFlg())
			{
				return;
			}
			auto otherOBB = other->GetComponent<CollisionObb>()->GetObb();
			auto myOBB = GetComponent<CollisionObb>()->GetObb();
			if (HitTest::OBB_OBB(otherOBB, myOBB)) {
				auto otherUp = other->GetComponent<Transform>()->GetPosition().y +
					other->GetComponent<Transform>()->GetScale().y / 2.0f;
				auto myDown = GetComponent<Transform>()->GetPosition().y -
					GetComponent<Transform>()->GetScale().y / 2.0f;
				m_startPos = GetComponent<Transform>()->GetPosition().y;
				m_dir = otherUp - myDown;
				m_bExtrude = true;
			}
		}
	}

	void Player::OnCollisionExcute(shared_ptr<GameObject>& other) {
		if (!bRespawn && !bMutekiFlg)
		{
			auto bDamegeTag = other->FindTag(L"damage");


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
		}
	}
}
//end basecross

