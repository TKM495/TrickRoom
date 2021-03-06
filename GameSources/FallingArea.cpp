/*!
@file FallingArea.cpp
@brief 落下判定エリアの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	FallingArea::FallingArea(const shared_ptr<Stage>& stage,
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
		m_bProjActive = Utility::WStrToBool(tokens[10]);
	}
	void FallingArea::OnCreate() {
		StageObject::ObjectSetUp();

		shared_ptr<SmBaseDraw> drawComp;
		if (m_bProjActive) {
			drawComp = AddComponent<PCTStaticDraw2>();
		}
		else {
			drawComp = AddComponent<PCTStaticDraw>();
		}
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		drawComp->SetDiffuse(Col4(0.0f, 0.0f, 0.0f, 1.0f));

		auto colComp = AddComponent<CollisionObb>();
		colComp->SetFixed(true);
		colComp->SetAfterCollision(AfterCollision::None);

		AddTag(L"FallingArea");
		AddTag(L"damage");
		SetDrawLayer(-1);
	}
}
//end basecross