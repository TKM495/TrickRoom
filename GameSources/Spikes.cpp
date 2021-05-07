/*!
@file Spikes.cpp
@brief 棘実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Spikes::Spikes(const shared_ptr<Stage>& stage,
		const wstring& line)
		:StageObject(stage)
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
		m_bProjActive = tokens[10] == L"TRUE" ? true : false;
		m_trickFlg = tokens[11] == L"TRUE" ? true : false;
		m_activeState = tokens[12] == L"Right" ? state::Right : state::Left;
	}

	void Spikes::OnCreate() {
		StageObject::ObjectSetUp();
		const auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();

		if (m_trickFlg) {
			if (scene->GetNowStageName() == L"ToTitleStage") {
				auto trick = AddComponent<TrickArtDrawTitle>();
				trick->SetMeshResource(L"Spikes");
				SetUpdateActive(false);
			}
			else {
				auto trick = AddComponent<TrickArtDraw>();
				trick->SetMeshResource(L"Spikes");
				trick->SetDir(m_activeState);
				trick->SetDiffuse(Col4(0.7f, 0.7f, 0.7f, 1.0f));
			}
			AddTag(L"TrickArtObj");
		}
		else {
			//auto shadowPtr = AddComponent<Shadowmap>();
			//shadowPtr->SetMeshResource(L"Spikes");
			if (m_bProjActive) {
				auto ptrDraw = AddComponent<PNTStaticDraw2>();
				ptrDraw->SetMeshResource(L"Spikes");
				ptrDraw->SetOwnShadowActive(true);
			}
			else {
				auto ptrDraw = AddComponent<PNTStaticDraw>();
				ptrDraw->SetMeshResource(L"Spikes");
				ptrDraw->SetOwnShadowActive(true);
			}
		}
		//OBB衝突判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		ptrColl->SetAfterCollision(AfterCollision::None);
		if (scene->GetDebugState() == DebugState::Debug) {
			ptrColl->SetDrawActive(true);
		}
		AddTag(L"damage");
	}
	void Spikes::OnUpdate() {
		UpdateArt<CollisionObb>(OnGetDrawCamera(), GetComponent<CollisionObb>());
	}
}
//end basecross
