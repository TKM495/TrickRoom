/*!
@file ResultStage.cpp
@brief ���ʉ�ʎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void ResultStage::CreateViewLight() {
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

	void ResultStage::OnCreate() {
		CreateViewLight();

		AddGameObject<UI_FPS>();

		auto csvLoad = AddGameObject<CSVLoad>();
		csvLoad->SpriteDataExtraction(App::GetApp()->GetScene<Scene>()->GetStringSpriteData(), SpriteType::String);
		csvLoad->SpriteDataExtraction(App::GetApp()->GetScene<Scene>()->GetImageSpriteData(), SpriteType::Image);

		auto scoreData = App::GetApp()->GetScene<Scene>()->GetScoreData();
		//�e�X�g�p�f�[�^
		scoreData.state = GameStage::GameState::CLEAR;
		scoreData.HP = 5;
		scoreData.BCrystal = 14;
		scoreData.RCrystal = 6;
		scoreData.Distance = 200;

		AddGameObject<Result>(scoreData);
		AddGameObject<ResultMenu>();
		AddGameObject<Fade>()->FadeIn();
	}

	void ResultStage::OnUpdate() {
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		//m_Inputhandler.PushHandle(GetThis<TitleStage>());
	}

}
//end basecross