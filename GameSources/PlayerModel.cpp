#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void PlayerModel::OnCreate() {
		auto drawComp = AddComponent<PNTStaticModelDraw>();
		drawComp->SetMeshResource(L"PlayerModel");

		auto shadow = AddComponent<Shadowmap>();
		shadow->SetMeshResource(L"PlayerModel");
	}
	void PlayerModel::OnUpdate() {
		//‚±‚±‚Åƒ‚[ƒVƒ‡ƒ“‚ğ“®‚©‚·
	}
}