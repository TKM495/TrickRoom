#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void PlayerModel::OnCreate() {
		auto drawComp = AddComponent<PNTStaticModelDraw>();
		drawComp->SetMultiMeshResource(L"PlayerModel");

		auto shadow = AddComponent<Shadowmap>();
		shadow->SetMultiMeshResource(L"PlayerModel");
	}
	void PlayerModel::OnUpdate() {
		//‚±‚±‚Åƒ‚[ƒVƒ‡ƒ“‚ğ“®‚©‚·
	}
}