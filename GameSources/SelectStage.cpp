/*!
@file SelectStage.cpp
@brief セレクトステージ(ステージセレクト画面)実装
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void SelectStage::CreateViewLight() {
		const Vec3 eye(0.0f, 10.0f, -10.0f);
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

		GameObjecttCSVBuilder builder;
		builder.Register<Player>(L"Player");
		builder.Register<Goal>(L"Goal");
		builder.Register<Plane>(L"Plane");
		builder.Register<Pillar>(L"Pillar");
		builder.Register<Block>(L"Block");
		builder.Register<Enemy>(L"Enemy");
		builder.Register<Spikes>(L"Spikes");
		builder.Register<SpikesArt>(L"SpikesArt");
		builder.Register<Stairs>(L"Stairs");
		builder.Register<PoleArt>(L"PoleArt");
		builder.Register<Crystal>(L"Crystal");
		builder.Register<Picture>(L"Picture");

		auto dir = App::GetApp()->GetDataDirWString();
		auto path = dir + L"Csv/SelectObject.csv";
		builder.Build(GetThis<Stage>(), path);

		auto csvLoad = AddGameObject<CSVLoad>();
		csvLoad->SpriteDataExtraction(App::GetApp()->GetScene<Scene>()->GetStringSpriteData(), SpriteType::String);
		csvLoad->SpriteDataExtraction(App::GetApp()->GetScene<Scene>()->GetImageSpriteData(), SpriteType::Image);
		auto arrow = AddGameObject<ImageSprite>(L"Arrow");
		arrow->SetSize(0.5f);
		arrow->SetPos(Vec3(500.0f, -100.0f, 0.0f));
		arrow = AddGameObject<ImageSprite>(L"Arrow");
		arrow->SetSize(0.5f);
		arrow->SetPos(Vec3(-500.0f, -100.0f, 0.0f));
		arrow->SetRot(180.0f);

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

	void SelectStage::RenderStage() {
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
//end basecross
