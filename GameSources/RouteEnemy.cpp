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
		m_activeState = tokens[12] == L"Right" ? state::Right : state::Left;

		m_speed = (float)_wtof(tokens[13].c_str());
	}
	void RouteEnemy::OnCreate() {
		if (m_trickFlg) {
			auto trick = AddComponent<TrickArtDraw>();
			trick->SetMeshResource(L"Enemy");
			trick->SetDir(m_activeState);
			AddTag(L"TrickArtObj");
		}
		else {
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
				auto ptrDraw = AddComponent<PNTStaticModelDraw>();
				ptrDraw->SetMeshResource(L"Enemy");
				ptrDraw->SetOwnShadowActive(true);
			}
		}

		auto col = AddComponent<CollisionSphere>();
		//これをつけるとOnCollisionEnterが呼ばれないのでコメントアウト
		//col->SetFixed(true);
		auto scene = App::GetApp()->GetScene<Scene>();
		if (scene->GetDebugState() == DebugState::Debug) {
			col->SetDrawActive(true);
		}

		StageObject::OnCreate();

		AddTag(L"Enemy");
		AddTag(L"damage");
		SetDrawLayer(-1);
	}

	void RouteEnemy::OnUpdate() {
		auto state = dynamic_pointer_cast<GameStage>(GetStage())->GetState();
		auto camera = dynamic_pointer_cast<MainCamera>(GetStage()->GetView()->GetTargetCamera());
		auto delta = App::GetApp()->GetElapsedTime();
		auto trans = GetComponent<Transform>();
		m_before = m_now;
		m_now = trans->GetPosition();
		switch (state)
		{
		default:
			if (camera->GetbLeapFlg()) {
				return;
			}
			GetBehavior<RouteMove>()->Excute();
			break;
		case basecross::GameStage::GameState::PAUSE:
			break;
		}
		UpdateArt<CollisionSphere>(OnGetDrawCamera(), GetComponent<CollisionSphere>());
		auto dir = m_before - m_now;
		if (dir.length() == 0.0f) {
			//遅延を入れる
			if (m_delta > 0.05f) {
				GetBehavior<RouteMove>()->Hit();
				m_delta = 0.0f;
			}
			m_delta += delta;
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