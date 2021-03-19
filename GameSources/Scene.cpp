
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

			auto& app = App::GetApp();
			auto dir = app->GetDataDirWString();
			auto path = dir + L"Csv/";
			CsvFile spriteCsv;
			spriteCsv.SetFileName(path + L"sprite.csv");
			spriteCsv.ReadCsv();
			m_spriteWData = spriteCsv.GetCsvVec();

			path = dir + L"Textures/";
			app->RegisterTexture(L"string", path + L"sprite.png");
			app->RegisterTexture(L"SpikesArt", path + L"Spikes.png");
			app->RegisterTexture(L"Cursor", path + L"Cursor.png");


			//クリアする色を設定
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTitleStage");
		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToTitleStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<TitleStage>();
		}
		if (event->m_MsgStr == L"ToGameStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<GameStage>();
		}
		if (event->m_MsgStr == L"ToExit") {
			exit(0);
		}
	}

}
//end basecross
