/*!
@file TitleStage.cpp
@brief タイトルステージ実体
*/

#include "stdafx.h"
#include "Project.h"
#include "TitleStage.h"

namespace basecross {

	void TitleStage::CreateViewLight() {
		const Vec3 eye(0.0f, 3.0f, -5.0f);
		const Vec3 at(0.0f, 3.0f, 5.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<TitleCamera>(eye);
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetBaseEye(eye);
		PtrCamera->SetAt(at);
		PtrCamera->SetPers(false);
		PtrCamera->SetWidth(9.0f);
		PtrCamera->SetHeight(PtrCamera->GetWidth() * 0.625f);
		//PtrCamera->SetFovY(0.6f);

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
		auto frame = AddGameObject<FrameSprite>(Vec2(500.0f,300.0f));
		frame->SetSize(0.5f);
		frame->SetPosition(Vec2(0.0f, -200.0f));

		AddGameObject<TitleMenu>();

		AddGameObject<TitleModel>();

		GameObjecttCSVBuilder builder;
		builder.Register<Player>(L"Player");
		builder.Register<Plane>(L"Plane");
		builder.Register<Block>(L"Block");
		auto dir = App::GetApp()->GetDataDirWString();
		auto path = dir + L"Csv/TitleObject.csv";
		builder.Build(GetThis<Stage>(), path);

		//タイトルに設置する錯視オブジェクト
		ObjectParam param[2] = {
			{Vec3(3.0f,2.0f,3.0f),Vec3(1.0f),Vec3(0.0f,0.0f,0.0f)},
			{Vec3(-3.0f,2.0f,3.0f),Vec3(1.0f),Vec3(0.0f,0.0f,0.0f)},
		};
		srand((unsigned int)time(NULL));
		int leftObj = rand() % 5;
		AddGameObject<illusionModel>(param[0], (illusionModel::Type)leftObj);
		int rightObj;
		do {
			rightObj = rand() % 5;
		} while (rightObj == leftObj);
		AddGameObject<illusionModel>(param[1],(illusionModel::Type)rightObj);


		AddGameObject<Fade>()->FadeIn();

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
		m_TADrawRenderTarget->ClearViews();
		m_TADrawRenderTarget->StartRenderTarget();
		//Dev->ClearDefaultViews();
		//Dev->StartDefaultDraw();
		const auto& Objs = GetGameObjectVec();
		for (auto& ptr : Objs) {
			if (ptr->IsDrawActive()) {
				auto TADraw = ptr->GetComponent<TrickArtDrawTitle>(false);
				if (TADraw) {
					TADraw->Active();
					TADraw->OnDraw();
				}
			}
		}
		//Dev->EndDefaultDraw();
		m_TADrawRenderTarget->EndRenderTarget();
		Stage::RenderStage();
	}

}