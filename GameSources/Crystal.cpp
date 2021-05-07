/*!
@file Crystal.cpp
@brief �N���X�^������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Crystal::Crystal(const shared_ptr<Stage>& stage,
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
		Vec3 scale;
		auto token = tokens[4];
		if (token == L"S") {
			scale = Vec3(0.5f);
		}
		else if (token == L"M") {
			scale = Vec3(0.65f);
		}
		else if (token == L"L") {
			scale = Vec3(0.7f);
		}
		else {
			scale = Vec3(1.0f);
		}
		m_scale = scale;

		Col4 color;
		token = tokens[5];
		if (token == L"Red") {
			color = Col4(1.0f, 0.0f, 0.0f, 1.0f);
		}
		else if (token == L"Green") {
			color = Col4(0.0f, 1.0f, 0.0f, 1.0f);
		}
		else if (token == L"Blue") {
			color = Col4(0.0f, 0.0f, 1.0f, 1.0f);
		}
		else {
			color = Col4(1.0f);
		}
		AddTag(token);
		m_color = color;
	}

	void Crystal::OnCreate() {
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		ptrDraw->SetMeshResource(L"Crystal");
		ptrDraw->SetDiffuse(m_color);
		ptrDraw->SetFogEnabled(true);
		ptrDraw->SetOwnShadowActive(true);

		auto shadowPtr = AddComponent<Shadowmap>();
		shadowPtr->SetMeshResource(L"Crystal");

		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetFixed(true);
		ptrColl->SetAfterCollision(AfterCollision::None);

		auto scene = App::GetApp()->GetScene<Scene>();
		if (scene->GetDebugState() == DebugState::Debug) {
			ptrColl->SetDrawActive(true);
		}

		StageObject::ObjectSetUp();

		AddTag(L"Crystal");
	}
}
//end basecross
