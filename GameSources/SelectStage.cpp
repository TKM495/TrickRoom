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
		auto arrow = AddGameObject<ImageSprite>(L"Arrow");
		arrow->SetSize(0.4f);
		arrow->SetPos(Vec2(550.0f, 0.0f));
		arrow->SetDrawLayer(5);
		arrow = AddGameObject<ImageSprite>(L"Arrow");
		arrow->SetSize(-0.4f);
		arrow->SetPos(Vec2(-550.0f, 0.0f));
		arrow->SetDrawLayer(5);

		auto frame = AddGameObject<FrameSprite>(Vec2(520.0f, 150.0f));
		frame->SetSize(0.5f);
		frame->SetPosition(Vec2(370.0f, -325.0f));
		auto aButton = AddGameObject<ImageSprite>(L"AButton");
		aButton->SetPos(Vec2(240.0f, -325.0f));
		aButton->SetSize(0.3f);
		auto bButton = AddGameObject<ImageSprite>(L"BButton");
		bButton->SetPos(Vec2(455.0f, -325.0f));
		bButton->SetSize(0.25f);
		auto title = AddGameObject<StringSprite2>(L"StageSelect2");
		title->SetPos(Vec2(0.0f, 330.0f));
		AddGameObject<SelectStageMenu>();

		AddGameObject<SceneTransition>()->Play(SceneTransition::TransDir::In);
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
