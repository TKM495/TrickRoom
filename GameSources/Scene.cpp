
/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate(){
		try {

			auto& app = App::GetApp();
			auto dir = app->GetDataDirWString();
			auto path = dir + L"Csv/";
			CsvFile csvFile;
			csvFile.SetFileName(path + L"Sprite.csv");
			csvFile.ReadCsv();
			m_spriteWData = csvFile.GetCsvVec();

			path = dir + L"Textures/";
			app->RegisterTexture(L"string", path + L"sprite.png");
			app->RegisterTexture(L"SpikesArt", path + L"Spikes.png");
			app->RegisterTexture(L"BlockArt", path + L"block.png");
			app->RegisterTexture(L"EnemyArt", path + L"Enemy.png");
			app->RegisterTexture(L"StairsArt", path + L"saka.png");
			app->RegisterTexture(L"Cursor", path + L"Cursor.png");

			path = dir + L"Models/";
			auto modelMesh = MeshResource::CreateStaticModelMesh(path + L"Enemy/", L"teki.bmf");
			app->RegisterResource(L"Enemy", modelMesh);
			modelMesh = MeshResource::CreateStaticModelMesh(path + L"Spikes/", L"Spikes.bmf");
			app->RegisterResource(L"Spikes", modelMesh);
			modelMesh = MeshResource::CreateStaticModelMesh(path, L"test.bmf");
			app->RegisterResource(L"TEST", modelMesh);
			modelMesh = MeshResource::CreateStaticModelMesh(path+L"Stairs/", L"saka.bmf");
			app->RegisterResource(L"Stairs", modelMesh);

			//�N���A����F��ݒ�
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToGameStage");
		}
		catch (...) {
			throw;
		}
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		//�^�C�g���X�e�[�W
		if (event->m_MsgStr == L"ToTitleStage") {
			ResetActiveStage<TitleStage>();
		}
		//�Z���N�g�X�e�[�W(�X�e�[�W�Z���N�g)
		if (event->m_MsgStr == L"ToSelectStage") {
			//ResetActiveStage<SelectStage>();
		}
		//�Q�[���X�e�[�W
		if (event->m_MsgStr == L"ToGameStage") {
			ResetActiveStage<GameStage>();
		}
		//�Q�[���I��
		if (event->m_MsgStr == L"ToExit") {
			exit(0);
		}
	}

}
//end basecross
