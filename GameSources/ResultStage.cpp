/*!
@file ResultStage.cpp
@brief ���ʉ�ʎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void ResultStage::CreateViewLight() {
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

	void ResultStage::OnCreate() {
		CreateViewLight();

		auto csvLoad = AddGameObject<CSVLoad>();
		csvLoad->SpriteDataExtraction(App::GetApp()->GetScene<Scene>()->GetSpriteData());

		auto scoreData = App::GetApp()->GetScene<Scene>()->GetScoreData();
		scoreData.state = GameStage::GameState::CLEAR;
		scoreData.HP = 10;
		scoreData.RCrystal = 12;
		scoreData.BCrystal = 34;
		scoreData.Distance = 57;

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
