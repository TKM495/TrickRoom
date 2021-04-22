/*!
@file TitleStage.cpp
@brief �^�C�g���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"
#include "TitleStage.h"

namespace basecross {

	void TitleStage::CreateViewLight() {
		const Vec3 eye(0.0f, 10.0f, -10.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	//void TitleStage::CreateSprite() {

	//}

	void TitleStage::OnCreate() {
		CreateViewLight();
		const auto& app = App::GetApp();

		auto csvLoad = AddGameObject<CSVLoad>();
		csvLoad->SpriteDataExtraction(App::GetApp()->GetScene<Scene>()->GetStringSpriteData(), SpriteType::String);
		auto title = AddGameObject<StringSprite2>(L"Title");
		title->GetComponent<Transform>()->SetPosition(Vec3(0.0f, 200.0f, 0.0f));
		AddGameObject<TitleMenu>();

		//GameObjecttCSVBuilder builder;
		//builder.Register<Player>(L"Player");
		//builder.Register<Goal>(L"Goal");
		//builder.Register<Plane>(L"Plane");
		//builder.Register<Pillar>(L"Pillar");
		//builder.Register<Block>(L"Block");
		//builder.Register<Enemy>(L"Enemy");
		//builder.Register<Spikes>(L"Spikes");
		//builder.Register<SpikesArt>(L"SpikesArt");
		//builder.Register<Stairs>(L"Stairs");
		//builder.Register<PoleArt>(L"PoleArt");
		//builder.Register<Crystal>(L"Crystal");
		//builder.Register<Picture>(L"Picture");

		//auto dir = app->GetDataDirWString();
		//auto path = dir + L"Csv/TitleObject.csv";
		//builder.Build(GetThis<Stage>(), path);

		//AddGameObject<BGSprite>(L"BackGround");
		AddGameObject<UI_FPS>();

		AddGameObject<Fade>()->FadeIn();

		//BGM�̍Đ�
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
		//BGM�̒�~
		auto audio = App::GetApp()->GetXAudio2Manager();
		audio->Stop(m_titleBGM);
	}

	//void TitleStage::PushB() {
	//	PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");
	//}

	void TitleStage::RenderStage() {
		//�`��f�o�C�X�̎擾
		auto Dev = App::GetApp()->GetDeviceResources();
		//�}���`�r���[���Ή�
		for (int i = 0; i < 2; i++) {
			m_TADrawRenderTarget[i]->ClearViews();
			m_TADrawRenderTarget[i]->StartRenderTarget();
			const auto& Objs = GetGameObjectVec();
			for (auto& ptr : Objs) {
				if (ptr->IsDrawActive()) {
					auto TADraw = ptr->GetComponent<TrickArtDraw>(false);
					if (TADraw) {
						//�����������Ȃ�
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