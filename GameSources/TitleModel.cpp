/*!
@file TitleModel.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TitleModel::OnCreate() {
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"Title");
		//drawComp->SetDir(state::Right);

		auto shadow = AddComponent<Shadowmap>();
		shadow->SetMeshResource(L"Title");

		auto trans = GetComponent<Transform>();
		trans->SetPosition(0.0f, 3.25f, 4.9f);
		trans->SetScale(Vec3(1.5f, 1.0f, 1.5f));
		trans->SetRotation(XMConvertToRadians(-90.0f), 0.0f, 0.0f);
		AddTag(L"TrickArtObj");
	}
}
//end basecross
