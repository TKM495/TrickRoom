/*!
@file Pole.cpp
@brief É|Å[Éãé¿ëÃ
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Pole::Pole(const shared_ptr<Stage>& stage,
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

	void Pole::OnCreate() {
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"Pole");
		StageObject::ObjectSetUp();

		auto coll = GetStage()->AddGameObject<AdvCollision>(GetThis<Pillar>(),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.25f, 1.0f, 0.25f),
			Vec3(0.0f, 0.0f, 0.0f),
			AdvCollision::Shape::Obb);
	}
}
//end basecross
