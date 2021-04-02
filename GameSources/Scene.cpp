
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate(){
		try {
			m_debugState = DebugState::None;

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
			app->RegisterTexture(L"FloorArt", path + L"RightPlane.png");
			app->RegisterTexture(L"Cursor", path + L"Cursor.png");
			app->RegisterTexture(L"time", path + L"time.png");
			app->RegisterTexture(L"heart", path + L"heart.png");
			app->RegisterTexture(L"crystal", path + L"crystal.png");
			app->RegisterTexture(L"point", path + L"point.png");
			app->RegisterTexture(L"PoleArt", path + L"Pole.png");

			app->RegisterTexture(L"Spark", path + L"spark.png");

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

			//クリアする色を設定
			Col4 Col;
			Col.set(0.5f, 0.5f, 0.7f, 1.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToResultStage");
		}
		catch (...) {
			throw;
		}
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		//タイトルステージ
		if (event->m_MsgStr == L"ToTitleStage") {
			ResetActiveStage<TitleStage>();
		}
		//セレクトステージ(ステージセレクト)
		if (event->m_MsgStr == L"ToSelectStage") {
			//ResetActiveStage<SelectStage>();
		}
		//ゲームステージ
		if (event->m_MsgStr == L"ToGameStage") {
			ResetActiveStage<GameStage>();
		}
		if (event->m_MsgStr == L"ToResultStage") {
			ResetActiveStage<ResultStage>();
		}
		//ゲーム終了
		if (event->m_MsgStr == L"ToExit") {
			exit(0);
		}
	}

}
//end basecross
