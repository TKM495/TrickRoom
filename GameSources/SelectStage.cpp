/*!
@file SelectStage.cpp
@brief セレクトステージ(ステージセレクト画面)実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void SelectStage::CreateViewLight() {
		const Vec3 eye(0.0f, 0.0f, -10.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void SelectStage::OnCreate() {
		CreateViewLight();

		AddGameObject<UI_FPS>();

		auto csvLoad = AddGameObject<CSVLoad>();
		csvLoad->SpriteDataExtraction(App::GetApp()->GetScene<Scene>()->GetStringSpriteData(), SpriteType::String);
		csvLoad->SpriteDataExtraction(App::GetApp()->GetScene<Scene>()->GetImageSpriteData(), SpriteType::Image);
		//auto arrow = AddGameObject<ImageSpriteForCSV>(L"Arrow");
		//arrow->SetSize(0.5f);
		//arrow->SetPos(Vec3(500.0f, 0.0f, 0.0f));
		//arrow = AddGameObject<ImageSpriteForCSV>(L"Arrow");
		//arrow->SetSize(0.5f);
		//arrow->SetPos(Vec3(-500.0f, 0.0f, 0.0f));
		//arrow->SetRot(180.0f);
		auto aButton = AddGameObject<ImageSprite>(L"AButton");
		aButton->SetPos(Vec2(250.0f, -325.0f));
		aButton->SetSize(0.3f);
		auto bButton = AddGameObject<ImageSprite>(L"BButton");
		bButton->SetPos(Vec2(470.0f, -325.0f));
		bButton->SetSize(0.25f);
		auto title = AddGameObject<StringSprite2>(L"StageSelect2");
		title->SetPos(Vec2(0.0f, 330.0f));
		AddGameObject<BGSprite>(L"BGSelectStage");
		AddGameObject<SelectStageMenu>();

		AddGameObject<Fade>()->FadeIn();
		//BGMの再生
		auto audio = App::GetApp()->GetXAudio2Manager();
		m_selectBGM = audio->Start(L"TitleBGM", XAUDIO2_LOOP_INFINITE, 0.1f);
	}

	void SelectStage::OnUpdate() {

	}

	void SelectStage::OnDestroy() {
		//BGMの停止
		auto audio = App::GetApp()->GetXAudio2Manager();
		audio->Stop(m_selectBGM);
	}
}
//end basecross
