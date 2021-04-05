/*!
@file Stairs.cpp
@brief 階段実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Stairs::Stairs(const shared_ptr<Stage>& stage,
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
	}

	void Stairs::OnCreate() {
		StageObject::OnCreate();

		auto drawComp = AddComponent<PNTStaticModelDraw>();
		drawComp->SetMeshResource(L"Stairs");
		drawComp->SetOwnShadowActive(true);

		auto stage = GetStage();
		//斜面用のコリジョン
		stage->AddGameObject<AdvCollision>(GetThis<Stairs>(),
			Vec3(0.0f, 0.5f, -0.5f),
			Vec3(1.0f, sqrtf(5.0f), 1.0f),
			Vec3(XMConvertToRadians(90.0f - 26.56f), 0.0f, 0.0f),
			AdvCollision::Shape::Rect);

		stage->AddGameObject<AdvCollision>(GetThis<Stairs>(),
			Vec3(0.0f, 0.125f, 0.0f),
			Vec3(1.0f, 0.25f, 1.0f),
			Vec3(0.0f),
			AdvCollision::Shape::Obb);
	}

	void Stairs::OnUpdate() {

	}
}
//end basecross
