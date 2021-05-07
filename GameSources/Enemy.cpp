/*!
@file Enemy.cpp
@brief
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Enemy::Enemy(const shared_ptr<Stage>& stage,
		const wstring& line)
		:StageObject(stage)
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

		m_behavior = tokens[13];
		m_cycle = (float)_wtof(tokens[14].c_str());
		m_speed = (float)_wtof(tokens[15].c_str());
		m_offset = (float)_wtof(tokens[16].c_str());
	}
	void Enemy::OnCreate() {
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
				auto ptrDraw = AddComponent<PNTStaticDraw>();
				ptrDraw->SetMeshResource(L"Enemy");
				ptrDraw->SetOwnShadowActive(true);
			}
		}

		auto col = AddComponent<CollisionSphere>();
		//これをつけるとOnCollisionEnterが呼ばれないのでコメントアウト
		col->SetFixed(true);
		auto scene = App::GetApp()->GetScene<Scene>();
		if (scene->GetDebugState() == DebugState::Debug) {
			col->SetDrawActive(true);
		}

		StageObject::ObjectSetUp();

		if (m_behavior == L"SinCurve") {
			GetBehavior<SinCurve>()->SetOffset(m_offset);
		}
		else if (m_behavior == L"SquareMove") {
			GetBehavior<SquareMove>()->SetSpeed(m_speed);
		}
		else if (m_behavior == L"CircularMove") {
			auto beha = GetBehavior<CircularMove>();
			beha->SetSpeed(m_speed);
			beha->SetRadius(m_cycle);
			beha->SetOffset(m_offset);
		}
		else {

		}

		AddTag(L"Enemy");
		AddTag(L"damage");
	}

	void Enemy::OnUpdate() {
		auto state = dynamic_pointer_cast<GameStage>(GetStage())->GetState();
		auto camera = dynamic_pointer_cast<MainCamera>(GetStage()->GetView()->GetTargetCamera());
		switch (state)
		{
		default:
			if (camera->GetbLeapFlg()) {
				return;
			}
			if (m_behavior == L"SinCurve") {
				GetBehavior<SinCurve>()->Excute(m_cycle, m_speed);
			}
			else if (m_behavior == L"SquareMove") {
				GetBehavior<SquareMove>()->Excute();
			}
			else if (m_behavior == L"CircularMove") {
				GetBehavior<CircularMove>()->Excute();
			}
			else {

			}
			break;
		case basecross::GameStage::GameState::PAUSE:
			break;
		}
		UpdateArt<CollisionSphere>(OnGetDrawCamera(), GetComponent<CollisionSphere>());
	}

	void Enemy::OnCollisionEnter(shared_ptr<GameObject>& other) {
		//オブジェクトを消してもいいと思ったが、念のため
		if (other->FindTag(L"damage")) {
			SetDrawActive(false);
			SetUpdateActive(false);
			AddNumTag(-1);
		}
	}
}
//end basecross