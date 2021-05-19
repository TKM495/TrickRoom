/*!
@file RouteEnemy.cpp
@brief
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	RouteEnemy::RouteEnemy(const shared_ptr<Stage>& stage,
		const wstring& line)
		:StageObject(stage),
		m_before(Vec3(0.0f)),
		m_now(Vec3(0.0f)),
		m_delta(0.0f)
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

		m_bProjActive = tokens[10] == L"TRUE" ? true : false;
		m_trickFlg = tokens[11] == L"TRUE" ? true : false;
		if (tokens[12] == L"Right") {
			m_activeState = state::Right;
		}
		else if (tokens[12] == L"Left") {
			m_activeState = state::Left;
		}
		else if (!m_trickFlg && tokens[12] == L"null") {
			//条件式を反転すれば下のelseと一緒にできるけど
			//とりあえず今はこのまま
		}
		else {
			throw BaseException(
				L"不明な文字列です。",
				L"m_activeState : " + tokens[12],
				L"RouteEnemy::RouteEnemy()"
			);
		}

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
				L"不明な文字列です。",
				L"m_activeState : " + tokens[13],
				L"RouteEnemy::RouteEnemy()"
			);
		}

		m_speed = (float)_wtof(tokens[14].c_str());
	}
	void RouteEnemy::OnCreate() {
		//影をつける（シャドウマップを描画する）
		auto shadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		shadowPtr->SetMeshResource(L"Enemy");
		if (m_bProjActive) {
			auto ptrDraw = AddComponent<PNTStaticDraw2>();
			ptrDraw->SetMeshResource(L"Enemy");
			ptrDraw->SetOwnShadowActive(true);
		}
		else {
			auto ptrDraw = AddComponent<PNTStaticDraw>();
			ptrDraw->SetMeshResource(L"Enemy");
			ptrDraw->SetOwnShadowActive(true);
		}


		auto col = AddComponent<CollisionSphere>();
		//これをつけるとOnCollisionEnterが呼ばれないのでコメントアウト
		//col->SetFixed(true);
		auto scene = App::GetApp()->GetScene<Scene>();
		if (scene->GetDebugState() == DebugState::Debug) {
			col->SetDrawActive(true);
		}

		StageObject::ObjectSetUp();
		GetBehavior<RouteMove>()->SetMoveDir(m_moveDir);
		AddTag(L"Enemy");
		AddTag(L"damage");
		SetDrawLayer(-1);
	}

	void RouteEnemy::OnUpdate() {
		auto state = dynamic_pointer_cast<GameStage>(GetStage())->GetState();
		auto camera = dynamic_pointer_cast<MainCamera>(GetStage()->GetView()->GetTargetCamera());
		auto delta = App::GetApp()->GetElapsedTime();
		auto trans = GetComponent<Transform>();
		if (camera->GetbLeapFlg()) {
			return;
		}
		m_before = m_now;
		m_now = trans->GetPosition();
		switch (state)
		{
		default:
			//GetBehavior<RouteMove>()->Excute();
			if ((m_before - m_now).length() == 0.0f) {
				//遅延を入れる
				if (m_delta > 0.05f) {
					GetBehavior<RouteMove>()->Hit();
					m_delta = 0.0f;
				}
				m_delta += delta;
			}
			break;
		case basecross::GameStage::GameState::PAUSE:
			break;
		}
	}

	void RouteEnemy::OnCollisionEnter(shared_ptr<GameObject>& other) {
		//オブジェクトを消してもいいと思ったが、念のため
		if (other->FindTag(L"damage")) {
			SetDrawActive(false);
			SetUpdateActive(false);
			AddNumTag(-1);
		}
	}
}
//end basecross