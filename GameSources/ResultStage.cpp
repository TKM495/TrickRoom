/*!
@file ResultStage.cpp
@brief 結果画面実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void ResultStage::CreateViewLight() {
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

	void ResultStage::OnCreate() {
		CreateViewLight();

		AddGameObject<UI_FPS>();

		auto csvLoad = AddGameObject<CSVLoad>();
		csvLoad->SpriteDataExtraction(App::GetApp()->GetScene<Scene>()->GetSpriteData());

		auto scoreData = App::GetApp()->GetScene<Scene>()->GetScoreData();
		//テスト用データ
		//scoreData.state = GameStage::GameState::CLEAR;
		//scoreData.HP = 5;
		//scoreData.BCrystal = 14;
		//scoreData.RCrystal = 6;
		//scoreData.Distance = 200;

		AddGameObject<Result>(scoreData);

		AddGameObject<ResultMenu>();
		AddGameObject<Fade>()->FadeIn();
	}

	void ResultStage::OnUpdate() {
		//コントローラチェックして入力があればコマンド呼び出し
		//m_Inputhandler.PushHandle(GetThis<TitleStage>());
	}

}
//end basecross
