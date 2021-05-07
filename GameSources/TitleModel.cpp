/*!
@file TitleModel.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TitleModel::OnCreate() {
		auto drawComp = AddComponent<TrickArtDrawTitle>();
		drawComp->SetMeshResource(L"Title");
		drawComp->SetDefPos(Vec3(0.0f, 1.8f, -5.0f));

		//AddComponent<PNTStaticDraw>()->SetMeshResource(L"Title");

		//auto shadow = AddComponent<Shadowmap>();
		//shadow->SetMeshResource(L"Title");

		auto trans = GetComponent<Transform>();
		trans->SetPosition(0.0f, 4.0f, 4.9f);
		trans->SetScale(Vec3(1.5f, 2.0f, 1.5f));
		trans->SetRotation(XMConvertToRadians(-90.0f), 0.0f, 0.0f);
		AddTag(L"TrickArtObj");
	}
}
//end basecross
