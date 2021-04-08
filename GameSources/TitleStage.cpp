/*!
@file TitleStage.cpp
@brief タイトルステージ実体
*/

#include "stdafx.h"
#include "Project.h"
#include "TitleStage.h"

namespace basecross {

	void TitleStage::CreateViewLight() {
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

	//void TitleStage::CreateSprite() {

	//}

	void TitleStage::OnCreate() {
		CreateViewLight();

		AddGameObject<UI_FPS>();

		auto csvLoad = AddGameObject<CSVLoad>();
		csvLoad->SpriteDataExtraction(App::GetApp()->GetScene<Scene>()->GetStringSpriteData(), SpriteType::String);
		auto title = AddGameObject<StringSprite2>(L"Title");
		title->GetComponent<Transform>()->SetPosition(Vec3(0.0f, 200.0f, 0.0f));
		AddGameObject<TitleMenu>();
		AddGameObject<Fade>()->FadeIn();

		//BGMの再生
		auto audio = App::GetApp()->GetXAudio2Manager();
		m_titleBGM = audio->Start(L"TitleBGM", XAUDIO2_LOOP_INFINITE, 0.1f);
	}

	void TitleStage::OnUpdate() {
		//コントローラチェックして入力があればコマンド呼び出し
		//m_Inputhandler.PushHandle(GetThis<TitleStage>());
	}

	void TitleStage::OnDestroy() {
		//BGMの停止
		auto audio = App::GetApp()->GetXAudio2Manager();
		audio->Stop(m_titleBGM);
	}

	//void TitleStage::PushB() {
	//	PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
	//}
}