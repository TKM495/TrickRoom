/*!
@file RouteFloor.cpp
@brief
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	RouteFloor::RouteFloor(const shared_ptr<Stage>& StagePtr,
		const wstring& line)
		:StageObject(StagePtr),
		m_bRespawn(false)
	{
		vector<wstring> tokens;
		Util::WStrToTokenVector(tokens, line, L',');
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
		//m_bProjActive = tokens[10] == L"TRUE" ? true : false;
		//m_trickFlg = tokens[11] == L"TRUE" ? true : false;
		//if (tokens[12] == L"Right") {
		//	m_activeState = state::Right;
		//}
		//else if (tokens[12] == L"Left") {
		//	m_activeState = state::Left;
		//}
		//else if (!m_trickFlg && tokens[12] == L"null") {
		//	//ðŒŽ®‚ð”½“]‚·‚ê‚Î‰º‚Ìelse‚Æˆê‚É‚Å‚«‚é‚¯‚Ç
		//	//‚Æ‚è‚ ‚¦‚¸¡‚Í‚±‚Ì‚Ü‚Ü
		//}
		//else {
		//	throw BaseException(
		//		L"•s–¾‚È•¶Žš—ñ‚Å‚·B",
		//		L"m_activeState : " + tokens[12],
		//		L"RouteEnemy::RouteEnemy()"
		//	);
		//}

		if (tokens[13] == L"Up") {
			m_moveDir = RouteMove::MoveDir::Up;
		}
		else if (tokens[13] == L"Left") {
			m_moveDir = RouteMove::MoveDir::Left;
		}
		else if (tokens[13] == L"Down") {
			m_moveDir = RouteMove::MoveDir::Down;
		}
		else if (tokens[13] == L"Right") {
			m_moveDir = RouteMove::MoveDir::Right;
		}
		else {
			throw BaseException(
				L"•s–¾‚È•¶Žš—ñ‚Å‚·B",
				L"m_activeState : " + tokens[13],
				L"RouteEnemy::RouteEnemy()"
			);
		}

		m_speed = (float)_wtof(tokens[14].c_str());
		m_respawnPos = m_position;
	}
	RouteFloor::~RouteFloor() {}

	void RouteFloor::OnCreate() {
		StageObject::ObjectSetUp();

		GetStage()->AddGameObject<FloorModel>(GetThis<RouteFloor>());

		auto col = AddComponent<CollisionObb>();
		col->AddExcludeCollisionTag(L"Player");
		auto scene = App::GetApp()->GetScene<Scene>();
		if (scene->GetDebugState() == DebugState::Debug) {
			col->SetDrawActive(true);
		}
		GetBehavior<RouteMove>()->SetMoveDir(m_moveDir);
		SetDrawLayer(-1);
		m_timer.SetCountTime(0.05f);
		m_timer.Reset();
	}

	void RouteFloor::OnUpdate() {
		auto state = dynamic_pointer_cast<GameStage>(GetStage())->GetState();
		auto camera = dynamic_pointer_cast<MainCamera>(GetStage()->GetView()->GetTargetCamera());
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto delta = App::GetApp()->GetElapsedTime();
		auto trans = GetComponent<Transform>();

		if (player->GetbRespawn() && player->GetMutekiFlg() && !m_bRespawn) {
			m_bRespawn = true;
		}
		if (!player->GetbRespawn() && player->GetMutekiFlg() && m_bRespawn) {
			m_bRespawn = false;
			trans->SetPosition(m_respawnPos);
		}

		if (camera->GetbLeapFlg()) {
			return;
		}
		m_before = m_now;
		m_now = trans->GetPosition();
		switch (state)
		{
		default:
			GetBehavior<RouteMove>()->Excute();
			m_move = m_before - m_now;
			if (m_move.length() <= m_speed * 0.2f) {
				//’x‰„‚ð“ü‚ê‚é
				if (m_timer.Count()) {
					GetBehavior<RouteMove>()->Hit();
					m_timer.Reset();
				}
			}
			break;
		case basecross::GameStage::GameState::PAUSE:
			break;
		}
	}
}
//end basecross
