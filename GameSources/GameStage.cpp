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

			//AddGameObject<FixedBox>(Vec3(20.0f,1.0f,20.0f), Vec3(0.0f), Vec3(0.0f,-1.0f,0.0f));
			AddGameObject<Player>();
			AddGameObject<SpikesArt>(5.0f);
			AddGameObject<Plane>(Vec3(0.0f,-1.0f,0.0f), Vec3(10.0f,1.0f,10.0f));
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
