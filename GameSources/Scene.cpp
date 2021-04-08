
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
			m_debugState = DebugState::None;

			//CSV�t�@�C��
			auto& app = App::GetApp();
			auto dir = app->GetDataDirWString();
			auto path = dir + L"Csv/";
			CsvFile csvFile;
			csvFile.SetFileName(path + L"StringSprite.csv");
			csvFile.ReadCsv();
			m_stringSpriteWData = csvFile.GetCsvVec();

			csvFile.SetFileName(path + L"ImageSprite.csv");
			csvFile.ReadCsv();
			m_imageSpriteWData = csvFile.GetCsvVec();

			csvFile.SetFileName(path + L"Picture.csv");
			csvFile.ReadCsv();
			m_pictureWData = csvFile.GetCsvVec();

			//�e�N�X�`��
			path = dir + L"Textures/";
			app->RegisterTexture(L"string", path + L"String.png");
			app->RegisterTexture(L"Sprite", path + L"Sprite.png");
			app->RegisterTexture(L"SpikesArt", path + L"Spikes.png");
			app->RegisterTexture(L"BlockArt", path + L"block.png");
			app->RegisterTexture(L"EnemyArt", path + L"Enemy.png");
			app->RegisterTexture(L"StairsArt", path + L"saka.png");
			app->RegisterTexture(L"FloorArt", path + L"RightPlane.png");
			app->RegisterTexture(L"Cursor", path + L"Cursor.png");
			app->RegisterTexture(L"VCursor", path + L"VerticalCursor.png");
			app->RegisterTexture(L"time", path + L"time.png");
			app->RegisterTexture(L"heart", path + L"heart.png");
			app->RegisterTexture(L"crystal", path + L"crystal.png");
			app->RegisterTexture(L"point", path + L"point.png");
			app->RegisterTexture(L"PoleArt", path + L"Pole.png");
			app->RegisterTexture(L"Spark", path + L"spark.png");
			app->RegisterTexture(L"C_Spark", path + L"spark.png");
			app->RegisterTexture(L"player", path + L"player.png");
			app->RegisterTexture(L"gauge", path + L"gauge.png");
			app->RegisterTexture(L"white", path + L"white.png");
			app->RegisterTexture(L"LR", path + L"left_right.png");
			app->RegisterTexture(L"ColorOut", path + L"ColorOut.png");
			app->RegisterTexture(L"UVCheck", path + L"UVCheck.png");

			//3D���f��
			path = dir + L"Models/";
			auto modelMesh = MeshResource::CreateStaticModelMesh(path + L"Enemy/", L"teki.bmf");
			app->RegisterResource(L"Enemy", modelMesh);
			modelMesh = MeshResource::CreateStaticModelMesh(path + L"Spikes/", L"Spikes.bmf");
			app->RegisterResource(L"Spikes", modelMesh);
			modelMesh = MeshResource::CreateStaticModelMesh(path, L"test.bmf");
			app->RegisterResource(L"TEST", modelMesh);
			modelMesh = MeshResource::CreateStaticModelMesh(path+L"Stairs/", L"saka.bmf");
			app->RegisterResource(L"Stairs", modelMesh);
			modelMesh = MeshResource::CreateStaticModelMesh(path+L"Crystal/", L"Crystal.bmf");
			app->RegisterResource(L"Crystal", modelMesh);
			modelMesh = MeshResource::CreateStaticModelMesh(path+L"Pillar/", L"Pillar.bmf");
			app->RegisterResource(L"Pillar", modelMesh);
			modelMesh = MeshResource::CreateStaticModelMesh(path+L"Title/", L"title.bmf");
			app->RegisterResource(L"Title", modelMesh);

			//BGM
			path = dir + L"Sound/BGM/";
			auto soundPath = path + L"TitleBGM.wav";
			app->RegisterWav(L"TitleBGM", soundPath);
			soundPath = path + L"GameBGM.wav";
			app->RegisterWav(L"GameBGM", soundPath);

			//SE
			path = dir + L"Sound/SE/";
			soundPath = path + L"Crystal2.wav";
			app->RegisterWav(L"CrystalSE", soundPath);
			soundPath = path + L"Damage2.wav";
			app->RegisterWav(L"DamageSE", soundPath);

			//�N���A����F��ݒ�
			Col4 Col;
			Col.set(0.5f, 0.5f, 0.7f, 1.0f);
			SetClearColor(Col);
			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToResultStage");
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
			ResetActiveStage<SelectStage>();
		}
		//�Q�[���X�e�[�W
		if (event->m_MsgStr == L"ToGameStage") {
			ResetActiveStage<GameStage>();
		}
		if (event->m_MsgStr == L"ToResultStage") {
			ResetActiveStage<ResultStage>();
		}
		//�Q�[���I��
		if (event->m_MsgStr == L"ToExit") {
			exit(0);
		}
	}

}
//end basecross
