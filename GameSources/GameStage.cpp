/*!
@file GameStage.cpp
@brief ゲームステージの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void GameStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//カメラの作成
		auto PtrCamera = ObjectFactory::Create<MainCamera>();
		PtrView->SetCamera(PtrCamera);
		//ライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::OnCreate() {
		try {
			//AddGameObject<Debug>();

			CreateViewLight();

			auto& app = App::GetApp();
			auto scene = app->GetScene<Scene>();
			auto csvLoad = AddGameObject<CSVLoad>();
			csvLoad->SpriteDataExtraction(scene->GetStringSpriteData(), SpriteType::String);

			GameObjecttCSVBuilder builder;
			builder.Register<Player>(L"Player");
			builder.Register<Plane>(L"Plane");
			builder.Register<VirtualFloor>(L"VFloor");
			builder.Register<Block>(L"Block");
			builder.Register<Enemy>(L"Enemy");
			builder.Register<Spikes>(L"Spikes");
			builder.Register<Stairs>(L"Stairs");
			builder.Register<StaticPlatePolygon>(L"StaticPlatePolygon");
			builder.Register<RouteEnemy>(L"RouteEnemy");
			builder.Register<RouteFloor>(L"RouteFloor");
			builder.Register<Battery>(L"Battery");
			builder.Register<FallingArea>(L"FallingArea");
			builder.Register<MovingFloor>(L"MovingFloor");
			builder.Register<Goal>(L"Goal");

			auto dir = app->GetDataDirWString();
			auto path = dir + L"Csv/Stage/Stage";
			path += to_wstring(m_stageNum);
			path += L".csv";

			builder.Build(GetThis<Stage>(), path);

			auto effect = AddGameObject<Effect>();
			SetSharedGameObject(L"Effect", effect);
			auto C_effect = AddGameObject<Effect>();
			SetSharedGameObject(L"C_Effect", C_effect);

			shared_ptr<GameObject> ui = AddGameObject<UI_Goalgauge>();
			m_uiObjs.push_back(ui);
			ui = AddGameObject<UI_Player>();
			m_uiObjs.push_back(ui);
			ui = AddGameObject<UI_LR>();
			m_uiObjs.push_back(ui);

			AddGameObject<Pause>();
			AddGameObject<BGSprite>(L"BackGround");
			AddGameObject<Fade>()->FadeIn();

			//BGM
			auto audio = App::GetApp()->GetXAudio2Manager();
			m_gameBGM = audio->Start(L"GameBGM", XAUDIO2_LOOP_INFINITE, 0.1f);

		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate() {
		const auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();
		const auto& pad = app->GetInputDevice().GetControlerVec()[0];
		auto fade = GetSharedGameObject<Fade>(L"Fade");
		switch (m_state)
		{
		case GameState::FADEIN:
			if (!fade->GetFadeActive()) {
				m_state = GameState::STAY;
				m_stateDelta = 0.0f;
				CreateStageNum();
			}
			break;
		case GameState::STAY:
			if (StartCountdown()) {
				m_state = GameState::PLAYING;
				m_stateDelta = 0.0f;
			}
			break;
		case GameState::PLAYING:
			if (pad.wPressedButtons & XINPUT_GAMEPAD_START) {
				SetState(GameState::PAUSE);
				GetSharedGameObject<Pause>(L"Pause")->IsActive(true);
			}
			break;
		case GameState::PAUSE:
			if (pad.wPressedButtons & XINPUT_GAMEPAD_START ||
				pad.wPressedButtons & XINPUT_GAMEPAD_B) {
				SetState(GameState::PLAYING);
				GetSharedGameObject<Pause>(L"Pause")->IsActive(false);
			}
			break;
		case GameState::CLEAR:
			break;
		case GameState::FADEOUT:
			if (!fade->GetFadeActive()) {
				PostEvent(0.0f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToResultStage");
			}
			break;
		default:
			break;
		}

		m_stateDelta += delta;
	}

	void GameStage::OnDestroy(){
		auto audio = App::GetApp()->GetXAudio2Manager();
		audio->Stop(m_gameBGM);
	}

	void GameStage::SetState(GameState state) {
		switch (state)
		{
		case GameState::CLEAR:
			for (auto& ui : m_uiObjs) {
				ui->SetDrawActive(false);
			}
			break;
		case GameState::FADEOUT:
			SetSceneTransition();
			break;
		default:
			break;
		}
		m_state = state;
	}

	void GameStage::SetSceneTransition() {
		auto fade = GetSharedGameObject<Fade>(L"Fade");
		fade->SetFadeColor(Col4(1.0f));
		fade->FadeOut();
	}

	void GameStage::CreateStageNum() {
		auto displayTime = 2.0f;
		auto basePos = Vec2(0.0f, 300.0f);

		auto frame = AddGameObject<FrameSprite>(Vec2(440.0f, 160.0f));
		frame->SetPosition(basePos + Vec2(30.0f, 0.0f));
		frame->SetSize(0.35f);
		frame->GetFadeComp()->SetFadeTime(0.1f);
		frame->GetFadeComp()->FadeIn();
		frame->Deactive(displayTime);
		frame->SetDrawLayer(2);

		auto str = AddGameObject<StringSprite2>(L"Stage",
			Align::Horizontal::Center,
			Align::Vertical::Center);
		str->SetSize(1.0f);
		str->SetPos(basePos);
		str->GetFadeComp()->SetFadeTime(0.1f);
		str->GetFadeComp()->FadeIn();
		str->Deactive(displayTime);
		str->SetDrawLayer(3);
		auto stageNum = App::GetApp()->GetScene<Scene>()->GetStageNum();
		auto obj = AddGameObject<Numbers>(stageNum);
		obj->SetSize(1.0f);
		obj->SetPos(basePos + Vec2(180.0f, 0.0f));
		obj->GetFadeComp()->SetFadeTime(0.1f);
		obj->GetFadeComp()->FadeIn();
		obj->Deactive(displayTime);
		obj->SetDrawLayer(3);
	}

	bool GameStage::StartCountdown() {
		auto delta = App::GetApp()->GetElapsedTime();
		auto deltaTime = 3.0f - m_stateDelta;
		bool flg = false;
		//数字の時
		if (deltaTime <= 1.0f) {
			auto str = AddGameObject<StringSprite2>(L"Start",
				Align::Horizontal::Center,
				Align::Vertical::Center,
				Col4(1.0f));
			str->SetSize(1.5f);
			str->GetFadeComp()->SetFadeTime(0.1f);
			str->GetFadeComp()->FadeIn();
			str->Deactive(1.0f);
			str->SetDrawLayer(1);
			flg = true;
		}
		m_beforeValue = (int)deltaTime;
		return flg;
	}

	void GameStage::RenderStage() {
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
