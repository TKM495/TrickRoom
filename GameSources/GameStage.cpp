/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<MainCamera>();
		PtrView->SetCamera(PtrCamera);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
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
			csvLoad->SpriteDataExtraction(scene->GetImageSpriteData(), SpriteType::Image);
			csvLoad->PictureDataExtraction(scene->GetPictureData());

			//�Q�[���I�u�W�F�N�g�r���_�[
			GameObjecttCSVBuilder builder;
			//�Q�[���I�u�W�F�N�g�̓o�^
			builder.Register<Player>(L"Player");
			builder.Register<Goal>(L"Goal");
			builder.Register<Plane>(L"Plane");
			builder.Register<Block>(L"Block");
			builder.Register<Enemy>(L"Enemy");
			builder.Register<Spikes>(L"Spikes");
			builder.Register<SpikesArt>(L"SpikesArt");
			builder.Register<Stairs>(L"Stairs");
			builder.Register<PoleArt>(L"PoleArt");
			builder.Register<Crystal>(L"Crystal");
			builder.Register<Picture>(L"Picture");
			builder.Register<RouteEnemy>(L"RouteEnemy");
			builder.Register<RouteFloor>(L"RouteFloor");
			builder.Register<Battery>(L"Battery");

			auto dir = app->GetDataDirWString();
			auto path = dir + L"Csv/Stage/Stage";
			path += to_wstring(m_stageNum);
			path += L".csv";

			builder.Build(GetThis<Stage>(), path);

			auto effect = AddGameObject<Effect>();
			SetSharedGameObject(L"Effect", effect);
			auto C_effect = AddGameObject<Effect>();
			SetSharedGameObject(L"C_Effect", C_effect);

			//AddGameObject<UI_HP>();
			//AddGameObject<UI_Crystal>();
			AddGameObject<UI_Goalgauge>();
			AddGameObject<UI_Player>();
			AddGameObject<UI_FPS>();
			AddGameObject<UI_LR>();

			AddGameObject<Pause>();
			AddGameObject<ColorOut>(Col4(1.0f), 0.25f, 0.0f, 4.0f);
			AddGameObject<BGSprite>(L"BackGround");
			AddGameObject<Fade>()->FadeIn();

			//BGM�̍Đ�
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
			if (pad.wPressedButtons & XINPUT_GAMEPAD_START) {
				SetState(GameState::PLAYING);
				GetSharedGameObject<Pause>(L"Pause")->IsActive(false);
			}
			break;
		case GameState::CLEAR:
			if (!fade->GetFadeActive()) {
				PostEvent(0.0f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToResultStage");
			}
			break;
		default:
			break;
		}

		m_stateDelta += delta;
		ObjDraw(0.1f);
	}

	void GameStage::OnDestroy(){
		//BGM�̒�~
		auto audio = App::GetApp()->GetXAudio2Manager();
		audio->Stop(m_gameBGM);
	}

	void GameStage::SetState(GameState state) {
		if (state == GameState::CLEAR) {
			SetSceneTransition();
		}
		m_state = state;
	}

	void GameStage::SetSceneTransition() {
		GetSharedGameObject<Fade>(L"Fade")->FadeOut();
	}

	void GameStage::CreateStageNum() {
		auto basePos = Vec2(0.0f, 300.0f);

		auto str = AddGameObject<StringSprite2>(L"Stage",
			Align::Horizontal::Center,
			Align::Vertical::Center);
		str->SetSize(1.0f);
		str->SetPos(basePos);
		str->GetFadeComp()->SetFadeTime(0.1f);
		str->GetFadeComp()->FadeIn();
		str->Deactive(1.0f);
		auto stageNum = App::GetApp()->GetScene<Scene>()->GetStageNum();
		auto obj = AddGameObject<Numbers>(stageNum);
		obj->SetSize(1.0f);
		obj->SetPos(basePos + Vec2(180.0f, 0.0f));
		obj->GetFadeComp()->SetFadeTime(0.1f);
		obj->GetFadeComp()->FadeIn();
		obj->Deactive(1.0f);
	}

	bool GameStage::StartCountdown() {
		auto delta = App::GetApp()->GetElapsedTime();
		auto deltaTime = 2.0f - m_stateDelta;
		bool flg = false;
		//数字の時
		if (deltaTime <= 1.0f) {
			auto str = AddGameObject<StringSprite2>(L"Start",
				Align::Horizontal::Center,
				Align::Vertical::Center);
			str->SetSize(1.5f);
			str->GetFadeComp()->SetFadeTime(0.1f);
			str->GetFadeComp()->FadeIn();
			str->Deactive(1.0f);
			flg = true;
		}
		m_beforeValue = (int)deltaTime;
		return flg;
	}

	void GameStage::ObjDraw(float time) {
		auto delta = App::GetApp()->GetElapsedTime();
		m_drawDelta += delta;
		if (m_drawDelta <= time) {
			return;
		}
		m_drawDelta = 0.0f;

		vector<shared_ptr<GameObject>> stageObjs;
		GetUsedTagObjectVec(L"StageObject", stageObjs);
		auto camera = dynamic_pointer_cast<MainCamera>(GetView()->GetTargetCamera());
		auto playerPos = camera->GetAt();
		for (auto& obj : stageObjs) {
			if (obj->FindTag(L"Plane") || obj->FindNumTag(-1)) {
				continue;
			}

			auto pos = obj->GetComponent<Transform>()->GetPosition();
			auto dir = playerPos - pos;
			if (dir.lengthSqr() > m_renderDis * m_renderDis) {
				obj->SetDrawActive(false);
				obj->SetUpdateActive(false);
			}
			else {
				obj->SetDrawActive(true);
				obj->SetUpdateActive(true);
			}
		}
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
