/*!
@file FallingArea.cpp
@brief —Ž‰º”»’èƒGƒŠƒA‚ÌŽÀ‘Ì
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
	}
	void FallingArea::OnCreate() {
		StageObject::ObjectSetUp();

		auto drawComp = AddComponent<PCTStaticDraw2>();
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