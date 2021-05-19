/*!
@file SelectStage.cpp
@brief �Z���N�g�X�e�[�W(�X�e�[�W�Z���N�g���)����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void SelectStage::CreateViewLight() {
		const Vec3 eye(0.0f, 0.0f, -10.0f);
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

	void SelectStage::OnCreate() {
		CreateViewLight();

		auto csvLoad = AddGameObject<CSVLoad>();
		csvLoad->SpriteDataExtraction(App::GetApp()->GetScene<Scene>()->GetStringSpriteData(), SpriteType::String);

		m_arrowsPos[0] = Vec2(550.0f, 0.0f);
		m_arrowsPos[1] = Vec2(-550.0f, 0.0f);

		m_arrows[0] = AddGameObject<ImageSprite>(L"Arrow");
		m_arrows[0]->SetSize(0.8f);
		m_arrows[0]->SetPos(m_arrowsPos[0]);
		m_arrows[0]->SetDrawLayer(5);
		m_arrows[1] = AddGameObject<ImageSprite>(L"Arrow");
		m_arrows[1]->SetSize(-0.8f);
		m_arrows[1]->SetPos(m_arrowsPos[1]);
		m_arrows[1]->SetDrawLayer(5);

		auto frame = AddGameObject<FrameSprite>(Vec2(520.0f, 150.0f));
		frame->SetSize(0.5f);
		frame->SetPosition(Vec2(370.0f, -325.0f));
		auto aButton = AddGameObject<ImageSprite>(L"AButton");
		aButton->SetPos(Vec2(240.0f, -325.0f));
		aButton->SetSize(0.3f);
		auto bButton = AddGameObject<ImageSprite>(L"BButton");
		bButton->SetPos(Vec2(455.0f, -325.0f));
		bButton->SetSize(0.25f);
		auto title = AddGameObject<StringSprite2>(L"StageSelect2");
		title->SetPos(Vec2(0.0f, 330.0f));
		m_menu = AddGameObject<SelectStageMenu>();

		AddGameObject<Fade>()->FadeIn();
		//BGM�̍Đ�
		auto audio = App::GetApp()->GetXAudio2Manager();
		m_selectBGM = audio->Start(L"TitleBGM", XAUDIO2_LOOP_INFINITE, 0.1f);
	}

	void SelectStage::OnUpdate() {
		float delta = App::GetApp()->GetElapsedTime();

		int groupNum = m_menu->GetMenuGroupNum();
		if (groupNum == 0) {
			m_arrows[1]->SetDrawActive(false);
		}
		else {
			m_arrows[1]->SetDrawActive(true);
		}
		if (groupNum == 3 - 1) {
			m_arrows[0]->SetDrawActive(false);
		}
		else {
			m_arrows[0]->SetDrawActive(true);
		}

		for (int i = 0; i < Utility::GetArrayLength(m_arrows); i++) {
			float dir = sin(m_delta * 3.0f) * 0.25f;
			if (i == 1) {
				dir *= -1.0f;
			}
			m_arrowsPos[i].x += dir;
			m_arrows[i]->GetComponent<Transform>()->SetPosition((Vec3)m_arrowsPos[i]);
		}

		if (m_delta >= XM_2PI) {
			m_delta = 0.0f;
		}
		m_delta += delta;
	}

	void SelectStage::OnDestroy() {
		//BGM�̒�~
		auto audio = App::GetApp()->GetXAudio2Manager();
		audio->Stop(m_selectBGM);
	}
}
//end basecross
