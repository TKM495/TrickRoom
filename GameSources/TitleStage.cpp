/*!
@file TitleStage.cpp
@brief タイトルステージ実体
*/

#include "stdafx.h"
#include "Project.h"
#include "TitleStage.h"

namespace basecross {

	void TitleStage::CreateViewLight() {
		const Vec3 eye(0.0f, 1.8f, -5.0f);
		const Vec3 at(0.0f, 1.8f, 5.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		PtrCamera->SetFovY(0.6f);

		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	//void TitleStage::CreateSprite() {

	//}

	void TitleStage::OnCreate() {
		CreateViewLight();
		const auto& app = App::GetApp();

		auto csvLoad = AddGameObject<CSVLoad>();
		csvLoad->SpriteDataExtraction(App::GetApp()->GetScene<Scene>()->GetStringSpriteData(), SpriteType::String);
		//auto title = AddGameObject<StringSprite2>(L"Title");
		//title->GetComponent<Transform>()->SetPosition(Vec3(0.0f, 200.0f, 0.0f));
		AddGameObject<TitleMenu>();

		AddGameObject<TitleModel>();

		GameObjecttCSVBuilder builder;
		builder.Register<Player>(L"Player");
		builder.Register<Plane>(L"Plane");
		builder.Register<Block>(L"Block");
		auto dir = App::GetApp()->GetDataDirWString();
		auto path = dir + L"Csv/TitleObject.csv";
		builder.Build(GetThis<Stage>(), path);

		AddGameObject<UI_FPS>();

		AddGameObject<SceneTransition>()->Play(SceneTransition::TransDir::In);

		//BGMの再生
		auto audio = App::GetApp()->GetXAudio2Manager();
		m_titleBGM = audio->Start(L"TitleBGM", XAUDIO2_LOOP_INFINITE, 0.1f);
	}

	void TitleStage::OnUpdate() {
		const auto& pad = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		if (pad.wPressedButtons & XINPUT_GAMEPAD_START) {
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
		}
	}

	void TitleStage::OnDestroy() {
		//BGMの停止
		auto audio = App::GetApp()->GetXAudio2Manager();
		audio->Stop(m_titleBGM);
	}

	//void TitleStage::PushB() {
	//	PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
	//}

	void TitleStage::RenderStage() {
		//描画デバイスの取得
		auto Dev = App::GetApp()->GetDeviceResources();

		//マルチビュー未対応
		for (int i = 0; i < 2; i++) {
			m_TADrawRenderTarget[i]->ClearViews();
			m_TADrawRenderTarget[i]->StartRenderTarget();
			const auto& Objs = GetGameObjectVec();
			for (auto& ptr : Objs) {
				if (ptr->IsDrawActive()) {
					auto TADraw = ptr->GetComponent<TrickArtDraw>(false);
					if (TADraw) {
						//方向が同じなら
						if ((int)TADraw->GetDir() == i) {
							TADraw->Active();
							TADraw->OnDraw();
						}
					}
				}
			}
			m_TADrawRenderTarget[i]->EndRenderTarget();
		}
		Stage::RenderStage();
	}

}