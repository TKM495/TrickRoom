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
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			//AddGameObject<Debug>();

			auto& app = App::GetApp();
			auto scene = app->GetScene<Scene>();
			auto csvLoad = AddGameObject<CSVLoad>();
			csvLoad->SpriteDataExtraction(scene->GetSpriteData());
			csvLoad->PictureDataExtraction(scene->GetPictureData());

			//�Q�[���I�u�W�F�N�g�r���_�[
			GameObjecttCSVBuilder builder;
			//�Q�[���I�u�W�F�N�g�̓o�^
			builder.Register<Player>(L"Player");
			builder.Register<Goal>(L"Goal");
			builder.Register<Plane>(L"Plane");
			builder.Register<Pillar>(L"Pillar");
			builder.Register<Block>(L"Block");
			builder.Register<BlockArt>(L"BlockArt");
			builder.Register<Enemy>(L"Enemy");
			builder.Register<EnemyArt>(L"EnemyArt");
			builder.Register<Spikes>(L"Spikes");
			builder.Register<SpikesArt>(L"SpikesArt");
			builder.Register<Stairs>(L"Stairs");
			builder.Register<StairsArt>(L"StairsArt");
			builder.Register<FloorArt>(L"FloorArt");
			builder.Register<PoleArt>(L"PoleArt");
			builder.Register<Crystal>(L"Crystal");
			builder.Register<Picture>(L"Picture");
			builder.Register<Pursuer>(L"Pursuer");

			auto dir = app->GetDataDirWString();
			auto path = dir + L"Csv/Object.csv";
			//auto& app = App::GetApp();
			//auto dir = app->GetDataDirWString();
			//auto path = dir + L"Csv/Object";
			//path += scene->GetNum();
			//path += L".csv";

			builder.Build(GetThis<Stage>(), path);

			//StageObject�̃^�O�����I�u�W�F�N�g��StageParent�̎q�ɂ���
			auto stagePar = AddGameObject<StageParent>();
			vector<shared_ptr<GameObject>> stageObjs;
			GetUsedTagObjectVec(L"StageObject", stageObjs);
			for (auto& obj : stageObjs) {
				obj->GetComponent<Transform>()->SetParent(stagePar);
			}
			stagePar->GetComponent<Transform>()->
				SetPosition(Vec3(-15.0f, 0.0f, 0.0f));

			auto effect = AddGameObject<Effect>(Vec3(-15.0f, 0.0f, 0.0f));
			effect->GetComponent<Transform>()->SetParent(stagePar);
			SetSharedGameObject(L"Effect", effect);

			AddGameObject<UI_HP>();
			AddGameObject<UI_Crystal>();
			AddGameObject<UI_Goalgauge>();
			AddGameObject<UI_Player>();
			AddGameObject<UI_FPS>();
			AddGameObject<UI_LR>();

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
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();
		auto fade = GetSharedGameObject<Fade>(L"Fade");

		switch (m_state)
		{
		case GameState::FADEIN:
			if (!fade->GetFadeActive()) {
				m_state = GameState::STAY;
			}
			break;
		case GameState::STAY:
		{ //文全体をかっこに入れるとエラーがでない
			auto str = AddGameObject<StringSprite2>(L"Start",
				Align::Horizontal::Center,
				Align::Vertical::Center,
				Col4(1.0f));
			str->SetSize(1.5f);
			str->GetFadeComp()->SetFadeTime(0.1f);
			str->GetFadeComp()->FadeIn();
			str->Deactive(1.0f);
			//AddGameObject<StartCountdown>()->Start();
			m_state = GameState::PLAYING;
		}
			break;
		case GameState::PLAYING:
			break;
		case GameState::PAUSE:
			break;
		case GameState::CLEAR:
			if (!fade->GetFadeActive()) {
				PostEvent(0.0f, GetThis<ObjectInterface>(), app->GetScene<Scene>(), L"ToResultStage");
			}
			break;
		case GameState::GAMEOVER:
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

	void GameStage::SetSceneTransition() {
		GetSharedGameObject<Fade>(L"Fade")->FadeOut();
	}

	void GameStage::ObjDraw(float time) {
		auto delta = App::GetApp()->GetElapsedTime();
		m_drawDelta += delta;
		if (m_drawDelta <= time) {
			return;
		}
		m_drawDelta = 0.0f;

		auto parent = GetSharedGameObject<StageParent>(L"StageParent");
		auto parentPos = parent->GetComponent<Transform>()->GetPosition();

		vector<shared_ptr<GameObject>> stageObjs;
		GetUsedTagObjectVec(L"StageObject", stageObjs);
		auto camera = dynamic_pointer_cast<MainCamera>(GetView()->GetTargetCamera());
		auto playerPos = camera->GetAt();
		for (auto& obj : stageObjs) {
			if (obj->FindTag(L"Plane") || obj->FindNumTag(-1)) {
				continue;
			}

			auto pos = obj->GetComponent<Transform>()->GetPosition();
			pos += parentPos;
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

}
//end basecross
