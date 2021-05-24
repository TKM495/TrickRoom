/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	vector<wstring>& Scene::GetStringSpriteData() { return m_stringSpriteWData; }
	vector<wstring>& Scene::GetImageSpriteData() { return m_imageSpriteWData; }
	vector<wstring>& Scene::GetPictureData() { return m_pictureWData; }
	vector<wstring>& Scene::GetStageScoreData() { return m_stageScoreWData; }

	DebugState Scene::GetDebugState() { return m_debugState; }
	shared_ptr<SoundItem> Scene::GetTitleBGM() { return m_titleBGM; }
	int Scene::GetStageNum() { return m_stageNum; }
	int Scene::GetMaxStage() { return m_maxStage; }

	wstring Scene::GetNowStageName() { return m_nowStageName; }
	wstring Scene::GetBeforeStageName() { return m_beforeStageName; }

	void Scene::SetTitleBGM(shared_ptr<SoundItem> bgm) {
		m_titleBGM = bgm;
	}
	void Scene::SetStageNum(int num) {
		m_stageNum = num;
	}

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

			csvFile.SetFileName(path + L"Stage/StageScore.csv");
			csvFile.ReadCsv();
			m_stageScoreWData = csvFile.GetCsvVec();

			//�e�N�X�`��
			path = dir + L"Textures/";
			app->RegisterTexture(L"string", path + L"String.png");
			app->RegisterTexture(L"Sprite", path + L"Sprite.png");
			app->RegisterTexture(L"SelectCursor", path + L"SelectCursor.png");
			app->RegisterTexture(L"VCursor", path + L"VerticalCursor.png");
			app->RegisterTexture(L"Triangle", path + L"Triangle.png");
			app->RegisterTexture(L"Spark", path + L"spark.png");
			app->RegisterTexture(L"C_Spark", path + L"spark.png");
			app->RegisterTexture(L"player", path + L"player.png");
			app->RegisterTexture(L"gauge", path + L"gauge.png");
			app->RegisterTexture(L"LR", path + L"left_right.png");
			app->RegisterTexture(L"ColorOut", path + L"ColorOut.png");
			app->RegisterTexture(L"Rank", path + L"Rank.png");
			app->RegisterTexture(L"Wall0", path + L"Wall0.png");
			app->RegisterTexture(L"Wall1", path + L"Wall1.png");
			app->RegisterTexture(L"Wall2", path + L"Wall2.png");
			app->RegisterTexture(L"Wall3", path + L"Wall3.png");
			app->RegisterTexture(L"Wall4", path + L"Wall4.png");
			app->RegisterTexture(L"Floor", path + L"Floor.png");
			app->RegisterTexture(L"PictureFrame", path + L"PictureFrame.png");
			app->RegisterTexture(L"PictureFrame2", path + L"PictureFrame2.png");
			app->RegisterTexture(L"AButton", path + L"AButton.png");
			app->RegisterTexture(L"BButton", path + L"BButton.png");
			app->RegisterTexture(L"ButtonFrame", path + L"ButtonFrame.png");
			app->RegisterTexture(L"ButtonFrame2", path + L"ButtonFrame2.png");
			app->RegisterTexture(L"BGSelectStage1", path + L"BGSelectStage1.png");
			app->RegisterTexture(L"BGSelectStage2", path + L"BGSelectStage2.png");
			app->RegisterTexture(L"BGSelectStage3", path + L"BGSelectStage3.png");
			app->RegisterTexture(L"BGSelectStage4", path + L"BGSelectStage4.png");
			app->RegisterTexture(L"Arrow", path + L"Arrow.png");
			app->RegisterTexture(L"BackGround", path + L"BGTest.png");
			app->RegisterTexture(L"Frame", path + L"Frame.png");
			app->RegisterTexture(L"1280x800", path + L"1280x800.png");
			//app->RegisterTexture(L"UVCheck", path + L"UVCheck.png");
			app->RegisterTexture(L"timer", path + L"time.png");
			app->RegisterTexture(L"heart", path + L"heart.png");
			app->RegisterTexture(L"crystal", path + L"crystal.png");
			app->RegisterTexture(L"point", path + L"point.png");
			app->RegisterTexture(L"StartPoint", path + L"StartPoint.png");
			app->RegisterTexture(L"GoalPoint", path + L"GoalPoint.png");
			app->RegisterTexture(L"White1x1", path + L"white.png");

			for (int i = 0; i < 3; i++) {
				auto num = to_wstring(i + 1);
				app->RegisterTexture(L"ButtonGuide" + num, path + L"ButtonGuide" + num + L".png");
			}

			for (int i = 1; i < GetMaxStage() + 1; i++) {
				auto stageNum = to_wstring(i);
				app->RegisterTexture(L"Stage" + stageNum + L"_tmb", path + L"thumbnail/Stage" + stageNum + L".png");
			}

			//3D���f��
			path = dir + L"Models/";
			auto modelMesh = MeshResource::CreateStaticModelMesh(path + L"Enemy/", L"teki.bmf");
			app->RegisterResource(L"Enemy", modelMesh);
			modelMesh = MeshResource::CreateStaticModelMesh(path + L"Spikes/", L"Spikes.bmf");
			app->RegisterResource(L"Spikes", modelMesh);
			modelMesh = MeshResource::CreateStaticModelMesh(path+L"Stairs/", L"saka.bmf");
			app->RegisterResource(L"Stairs", modelMesh);
			modelMesh = MeshResource::CreateStaticModelMesh(path+L"Crystal/", L"Crystal.bmf");
			app->RegisterResource(L"Crystal", modelMesh);
			modelMesh = MeshResource::CreateStaticModelMesh(path+L"Battery/", L"Battery.bmf");
			app->RegisterResource(L"Battery", modelMesh);
			modelMesh = MeshResource::CreateStaticModelMesh(path+L"Title/", L"title.bmf");
			app->RegisterResource(L"Title", modelMesh);

			auto goalModelMesh = MeshResource::CreateBoneModelMesh(path + L"Goal/", L"door.bmf");
			app->RegisterResource(L"Goal", goalModelMesh);

			auto trickPath = path + L"illusionModel/";
			modelMesh = MeshResource::CreateStaticModelMesh(trickPath + L"Triangle/", L"Triangle.bmf");
			app->RegisterResource(L"TriangleModel", modelMesh);
			modelMesh = MeshResource::CreateStaticModelMesh(trickPath + L"Stairs/", L"Stairs.bmf");
			app->RegisterResource(L"StairsModel", modelMesh);
			modelMesh = MeshResource::CreateStaticModelMesh(trickPath + L"Cube/", L"Cube.bmf");
			app->RegisterResource(L"CubeModel", modelMesh);
			modelMesh = MeshResource::CreateStaticModelMesh(trickPath + L"Arch/", L"Arch.bmf");
			app->RegisterResource(L"ArchModel", modelMesh);
			modelMesh = MeshResource::CreateStaticModelMesh(trickPath + L"Rectangle/", L"Rectangle.bmf");
			app->RegisterResource(L"RectangleModel", modelMesh);

			auto playerModelMesh = MeshResource::CreateBoneModelMesh(path + L"Player/", L"Player2.bmf");
			app->RegisterResource(L"PlayerModel", playerModelMesh);

			//BGM
			path = dir + L"Sound/BGM/";
			app->RegisterWav(L"TitleBGM", path + L"TitleBGM.wav");
			app->RegisterWav(L"GameBGM", path + L"GameBGM.wav");
			app->RegisterWav(L"GameClear", path + L"GameClear.wav");

			//SE
			path = dir + L"Sound/SE/";
			app->RegisterWav(L"CrystalSE", path + L"Crystal2.wav");
			app->RegisterWav(L"DamageSE", path + L"Damage2.wav");
			app->RegisterWav(L"CursorSE", path + L"Cursor.wav");
			app->RegisterWav(L"DecisionSE", path + L"Decision.wav");
			app->RegisterWav(L"CancelSE", path + L"Cancel.wav");

			app->RegisterWav(L"DoorOpenSE", path + L"DoorOpen.wav");
			app->RegisterWav(L"DoorCloseSE", path + L"DoorClose.wav");
			app->RegisterWav(L"FallSE", path + L"Fall.wav");
			app->RegisterWav(L"PauseMenuOpenSE", path + L"PauseMenuOpen.wav");
			app->RegisterWav(L"PauseMenuCloseSE", path + L"PauseMenuClose.wav");
			app->RegisterWav(L"WalkSE", path + L"Walk.wav");
			app->RegisterWav(L"FloorMoveSE", path + L"FloorMove.wav");
			app->RegisterWav(L"IncorrectSE", path + L"Incorrect.wav");

			//�N���A����F��ݒ�
			Col4 Col;
			Col.set(0.5f, 0.5f, 0.7f, 1.0f);
			SetClearColor(Col);
			m_nowStageName = L"Startup";
			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToGameStage");
		}
		catch (...) {
			throw;
		}
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		m_beforeStageName = m_nowStageName;
		m_nowStageName = event->m_MsgStr;
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
			ResetActiveStage<GameStage>(GetStageNum());
		}
		if (event->m_MsgStr == L"ToResultStage") {
			ResetActiveStage<ResultStage>();
		}
		if (event->m_MsgStr == L"ToGoalStage") {
			ResetActiveStage<GoalStage>();
		}
		//�Q�[���I��
		if (event->m_MsgStr == L"ToExit") {
			PostQuitMessage(0);
		}
	}

}
//end basecross
