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
		m_moveSpeed(2), m_HP(3), m_Crystal(0),
		bMutekiFlg(false), m_Mcount(0), m_MTime(2),
		m_DrawCount(0), m_BlinkMask(8), rotationSpeed(0.2f),
		m_bExtrude(false), m_deltaExtrude(0.0f),
		bDotFlg(false), m_DotCount(0), m_DotMaxCount(2),
		m_count(0), m_RespawnTime(2), bRespawn(false), m_nowMoveSp(Vec3(0.0f)),
		m_bClear(false), m_nowPos(Vec3(0.0f)), m_beforePos(Vec3(0.0f)), m_bFalling(false)
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
			XMConvertToRadians((float)_wtof(tokens[8].c_str()) + 90.0f),
			XMConvertToRadians((float)_wtof(tokens[9].c_str()))
		);
		m_respawnPos = m_position;
		m_respawnPos.y += 0.5f;
	}

	void Player::OnCreate()
	{
		GetStage()->SetSharedGameObject(L"Player", GetThis<Player>());

		m_model = GetStage()->AddGameObject<PlayerModel>(GetThis<Player>());
		auto trans = m_model->GetComponent<Transform>();
		trans->SetParent(GetThis<Player>());
		trans->SetPosition(Vec3(0.0f, -0.75f, 0.0f));

		auto pos = m_respawnPos;
		pos.y = 0.01f;
		GetStage()->AddGameObject<StartPoint>(pos);

		AddTag(L"Player");

		auto grav = AddComponent<Gravity>();
		auto col = AddComponent<CollisionObb>();
		auto scene = App::GetApp()->GetScene<Scene>();
		if (scene->GetDebugState() == DebugState::Debug) {
			col->SetDrawActive(true);
		}

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		transComp->SetScale(m_scale);
		transComp->SetRotation(m_rotation);

		//ステートマシンの構築
		m_StateMachine.reset(new StateMachine<Player>(GetThis<Player>()));
		//初期ステートの設定
		m_StateMachine->ChangeState(PlayerStartState::Instance());
	}

	Vec3 Player::MoveVec()
	{
		auto stage = dynamic_pointer_cast<GameStage>(GetStage());

		auto camera = OnGetDrawCamera();

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
		m_beforePos = m_nowPos;
		m_StateMachine->Update();
		m_nowPos = GetComponent<Transform>()->GetPosition();
	}

	void Player::StartInit() {
		GetComponent<Gravity>()->SetUpdateActive(false);
		GetComponent<CollisionObb>()->SetUpdateActive(false);
	}

	void Player::DefaultInit() {
		auto scene = App::GetApp()->GetScene<Scene>();
		if ((scene->GetDebugState() == DebugState::CreateStage)) {
			m_moveSpeed = 10.0f;
		}
		else {
			GetComponent<Gravity>()->SetUpdateActive(true);
			GetComponent<CollisionObb>()->SetUpdateActive(true);
		}
	}

	void Player::DefaultBehavior(){
		auto stage = GetStage();

		auto camera = stage->GetView()->GetTargetCamera();
		auto mainCamera = dynamic_pointer_cast<MainCamera>(camera);

		if (m_bExtrude) {
			auto delta = App::GetApp()->GetElapsedTime();
			auto pos = GetComponent<Transform>()->GetPosition();
			pos.y = Lerp::CalculateLerp(m_basePosY, m_basePosY + m_dir, 0.0, 1.0f, m_deltaExtrude, Lerp::rate::Linear);
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
				Muteki();
			}
		}
		else {
			Respawn();
		}

		//点滅フラグ == true && 落下死ではないとき
		if (bDotFlg && !m_bFalling)
		{
			Draw();
		}

		//if (m_HP <= 1) {
		//	auto colorout = stage->GetSharedGameObject<ColorOut>(L"ColorOut");
		//	colorout->SetColor(Col4(1.0f, 0.0f, 0.0f, 1.0f));
		//	colorout->SetRange(0.25f, 0.0f);
		//	colorout->SetActive(true);
		//}
	}

	void Player::GoalInit() {
		auto stage = GetTypeStage<GameStage>();
		auto goalPosForward = stage->GetGoalPosForward();
		auto goalPos = goalPosForward.origin;
		auto goalForward = goalPosForward.dir;

		auto transComp = GetComponent<Transform>();
		m_startPos = transComp->GetPosition();
		m_middlePos = goalPos + (goalForward * 1.5f);
		m_endPos = goalPos;

		m_bClear = true;
		//m_model->SetDrawActive(false);
		stage->SetState(GameStage::GameState::CLEAR);
		m_startToMiddleTime = (m_startPos - m_middlePos).length() / m_moveSpeed;
		m_middleToEndTime = (m_middlePos - m_endPos).length() / m_moveSpeed;
		m_appealTime = 2.0f;
		m_moveTime = m_startToMiddleTime + m_middleToEndTime + m_appealTime;
		m_timer.SetCountTime(m_moveTime);
	}

	void Player::GoalBehavior() {
		if (m_timer.GetTime() < m_startToMiddleTime) {
			auto pos = Lerp::CalculateLerp(m_startPos, m_middlePos,
				0.0f, m_startToMiddleTime,
				m_timer.GetTime(), Lerp::rate::Linear);
			GetComponent<Transform>()->SetPosition(pos);
			auto utilPtr = GetBehavior<UtilBehavior>();
			auto dir = m_startPos - m_middlePos;
			utilPtr->RotToHead(dir.normalize(), rotationSpeed);
		}
		else if (m_timer.GetTime() < m_appealTime + m_startToMiddleTime) {
			auto pos = GetComponent<Transform>()->GetPosition();
			auto eye = OnGetDrawCamera()->GetEye();
			eye.y = pos.x;
			auto dir = pos - eye;
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(dir.normalize(), rotationSpeed);
		}
		else if (m_timer.GetTime() < m_moveTime) {
			auto pos = Lerp::CalculateLerp(m_middlePos, m_endPos,
				0.0f, m_middleToEndTime,
				m_timer.GetTime() - (m_startToMiddleTime + m_appealTime), Lerp::rate::Linear);
			GetComponent<Transform>()->SetPosition(pos);
			auto utilPtr = GetBehavior<UtilBehavior>();
			auto dir = m_middlePos - m_endPos;
			utilPtr->RotToHead(dir.normalize(), rotationSpeed);
		}

		if (m_timer.Count(m_middleToEndTime)) {
			auto stage = GetTypeStage<GameStage>();
			//以下のstage->SetState(GameStage::GameState::FADEOUT);は
			//常時実行できないのでここではじく
			if (stage->GetState() == GameStage::GameState::FADEOUT) {
				return;
			}
			stage->SetState(GameStage::GameState::FADEOUT);
			stage->GetSharedGameObject<GoalModel>(L"GoalModel")->GetStateMachine()->ChangeState(GoalModelOpen::Instance());
		}
	}

	void Player::Move()
	{
		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();

		m_nowMoveSp = MoveVec();
		pos += m_nowMoveSp;

		transComp->SetPosition(pos);

		if (MoveVec().length() > 0.0f)
		{
			auto utilPtr = GetBehavior<UtilBehavior>();
			//3Dモデルの正面が逆なのでマイナス
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
			bRespawn = false;
			m_bFalling = false;
			auto transComponent = GetComponent<Transform>();
			transComponent->SetPosition(m_respawnPos);
			GetComponent<Collision>()->SetUpdateActive(true);
			GetComponent<Gravity>()->SetUpdateActive(true);

			m_count = 0;
		}

	}

	//点滅
	void Player::Draw()
	{
		auto& app = App::GetApp();
		float ElapsedTime = app->GetElapsedTime();

		m_DotCount += ElapsedTime;

		if (m_DrawCount & m_BlinkMask)
		{
			m_model->SetDrawActive(true);
		}
		else
		{
			m_model->SetDrawActive(false);
		}

		++m_DrawCount;

	}

	void Player::Muteki()
	{
		auto& app = App::GetApp();
		float ElapsedTime = app->GetElapsedTime();

		m_Mcount += ElapsedTime;

		if (m_Mcount > m_MTime)
		{
			bDotFlg = false;
			m_model->SetDrawActive(true);
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
		return m_Crystal;
	}

	//衝突判定
	void Player::OnCollisionEnter(std::shared_ptr<GameObject>& other)
	{
		//auto bCrystalTag = other->FindTag(L"Crystal");
		//if (bCrystalTag)
		//{
		//	//auto ColComp = GetComponent<Collision>();

		//	//ColComp->AddExcludeCollisionTag(L"crystal");

		//	auto effect = GetStage()->GetSharedGameObject<Effect>(L"C_Effect");
		//	effect->CrystalEffect(other->GetComponent<Transform>()->GetPosition());

		//	other->SetDrawActive(false);
		//	other->SetUpdateActive(false);
		//	other->AddNumTag(-1);

		//	//SE
		//	auto audio = App::GetApp()->GetXAudio2Manager();
		//	audio->Start(L"CrystalSE", 0, 0.1f);
		//}

		//OnCollisionExcute()のほうにも入れているが弾の判定が取れないため
		//こちらにも入れる
		if (!bRespawn && !bMutekiFlg)
		{
			auto bDamegeTag = other->FindTag(L"damage");
			if (bDamegeTag)
			{
				//m_HP += -1;
				bRespawn = true;
				bMutekiFlg = true;
				bDotFlg = true;

				m_DotCount = 0;

				GetComponent<Collision>()->SetUpdateActive(false);
				GetComponent<Gravity>()->SetUpdateActive(false);
				if (other->FindTag(L"FallingArea")) {
					auto audio = App::GetApp()->GetXAudio2Manager();
					audio->Start(L"FallSE", 0, 0.1f);
					m_bFalling = true;
					m_model->SetDrawActive(false);
				}
				else {
					auto effect = GetStage()->GetSharedGameObject<Effect>(L"Effect");
					effect->InsertEffect(other->GetComponent<Transform>()->GetPosition());
					auto audio = App::GetApp()->GetXAudio2Manager();
					audio->Start(L"DamageSE", 0, 0.1f);
				}
			}
		}

		if (other->FindTag(L"Goal")) {
			m_StateMachine->ChangeState(PlayerGoalState::Instance());
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
				m_basePosY = GetComponent<Transform>()->GetPosition().y;
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
				//m_HP += -1;
				bRespawn = true;
				bMutekiFlg = true;
				bDotFlg = true;

				m_DotCount = 0;

				GetComponent<Collision>()->SetUpdateActive(false);
				GetComponent<Gravity>()->SetUpdateActive(false);
				if (other->FindTag(L"FallingArea")) {
					auto audio = App::GetApp()->GetXAudio2Manager();
					audio->Start(L"FallSE", 0, 0.1f);
					m_bFalling = true;
					m_model->SetDrawActive(false);
				}
				else {
					auto effect = GetStage()->GetSharedGameObject<Effect>(L"Effect");
					effect->InsertEffect(other->GetComponent<Transform>()->GetPosition());
					auto audio = App::GetApp()->GetXAudio2Manager();
					audio->Start(L"DamageSE", 0, 0.1f);
				}
			}
		}
	}

	shared_ptr<PlayerStartState> PlayerStartState::Instance() {
		static shared_ptr<PlayerStartState> instance(new PlayerStartState);
		return instance;
	}
	void PlayerStartState::Enter(const shared_ptr<Player>& Obj) {
		Obj->StartInit();
	}
	void PlayerStartState::Execute(const shared_ptr<Player>& Obj) {
		auto stage = Obj->GetTypeStage<GameStage>();
		if (stage->GetState() == GameStage::GameState::PLAYING) {
			Obj->GetStateMachine()->ChangeState(PlayerDefaultState::Instance());
		}
	}
	void PlayerStartState::Exit(const shared_ptr<Player>& Obj) {}

	shared_ptr<PlayerDefaultState> PlayerDefaultState::Instance() {
		static shared_ptr<PlayerDefaultState> instance(new PlayerDefaultState);
		return instance;
	}
	void PlayerDefaultState::Enter(const shared_ptr<Player>& Obj) {
		Obj->DefaultInit();
	}
	void PlayerDefaultState::Execute(const shared_ptr<Player>& Obj) {
		Obj->DefaultBehavior();
	}
	void PlayerDefaultState::Exit(const shared_ptr<Player>& Obj) {}

	shared_ptr<PlayerGoalState> PlayerGoalState::Instance() {
		static shared_ptr<PlayerGoalState> instance(new PlayerGoalState);
		return instance;
	}
	void PlayerGoalState::Enter(const shared_ptr<Player>& Obj) {
		Obj->GoalInit();
	}
	void PlayerGoalState::Execute(const shared_ptr<Player>& Obj) {
		Obj->GoalBehavior();
	}
	void PlayerGoalState::Exit(const shared_ptr<Player>& Obj) {}
}
//end basecross

