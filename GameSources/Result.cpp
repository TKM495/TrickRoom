/*!
@file Result.cpp
@brief Œ‹‰ÊŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Result::OnCreate() {
		auto stageNum = App::GetApp()->GetScene<Scene>()->GetStageNum();

		wstring titleStr = L"";

		auto stage = GetStage();
		auto back = stage->AddGameObject<PictureFrame>(Vec2(1000.0f, 640.0f), false);
		back->SetPos(Vec2(0.0f, 120.0f));

		//ƒ^ƒCƒgƒ‹‚Íˆê‚Â‚È‚Ì‚Å•Êˆ—
		auto title = stage->AddGameObject<StringSprite2>(L"StageClear");
		title->GetComponent<Transform>()->SetPosition(Vec3(0.0f, 320.0f, 0.0f));

		auto image = stage->AddGameObject<ImageSprite>(L"1280x800");
		image->SetPos(Vec2(0.0f, 80.0f));
		image->SetSize(0.5f);
	}
}
//end basecross
