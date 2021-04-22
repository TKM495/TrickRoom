/*!
@file ResultStage.cpp
@brief 結果画面実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void ResultStage::CreateViewLight() {
		const Vec3 eye(0.0f, 2.0f, -10.0f);
		const Vec3 at(0.0f, 1.8f, 5.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		PtrCamera->SetFovY(0.4f);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void ResultStage::OnCreate() {
		CreateViewLight();

		AddGameObject<UI_FPS>();

		auto csvLoad = AddGameObject<CSVLoad>();
		csvLoad->SpriteDataExtraction(App::GetApp()->GetScene<Scene>()->GetStringSpriteData(), SpriteType::String);
		csvLoad->SpriteDataExtraction(App::GetApp()->GetScene<Scene>()->GetImageSpriteData(), SpriteType::Image);

		GameObjecttCSVBuilder builder;
		builder.Register<Player>(L"Player");
		builder.Register<Plane>(L"Plane");
		builder.Register<Block>(L"Block");

		auto dir = App::GetApp()->GetDataDirWString();
		auto path = dir + L"Csv/ResultObject.csv";
		builder.Build(GetThis<Stage>(), path);

		auto scoreData = App::GetApp()->GetScene<Scene>()->GetScoreData();

		AddGameObject<Result>(scoreData);

		AddGameObject<ResultMenu>();

		//AddGameObject<BGSprite>(L"BGClear");

		AddGameObject<Fade>()->FadeIn();

		auto audio = App::GetApp()->GetXAudio2Manager();
		wstring bgmName = L"";

		audio->Start(L"GameClear", 0, 0.1f);
	}
}
//end basecross
