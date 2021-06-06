/*!
@file LoadStage.cpp
@brief ロードステージの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	bool LoadStage::m_Loaded = false;
	mutex LoadStage::mtx;

	void LoadStage::LoadResourceFunc() {
		mtx.lock();
		m_Loaded = false;
		mtx.unlock();

		//リソースの読み込み
		auto& app = App::GetApp();
		auto scene = app->GetScene<Scene>();
		auto dir = app->GetDataDirWString();
		//テクスチャ
		auto path = dir + L"Textures/";
		app->RegisterTexture(L"string", path + L"String.png");
		app->RegisterTexture(L"SelectCursor", path + L"SelectCursor.png");
		app->RegisterTexture(L"Triangle", path + L"Triangle.png");
		app->RegisterTexture(L"Spark", path + L"spark.png");
		app->RegisterTexture(L"player", path + L"player.png");
		app->RegisterTexture(L"gauge", path + L"gauge.png");
		app->RegisterTexture(L"LR", path + L"left_right.png");
		app->RegisterTexture(L"Wall0", path + L"Wall0.png");
		app->RegisterTexture(L"Wall1", path + L"Wall1.png");
		app->RegisterTexture(L"Wall2", path + L"Wall2.png");
		app->RegisterTexture(L"Wall3", path + L"Wall3.png");
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
		app->RegisterTexture(L"Arrow", path + L"Arrow.png");
		app->RegisterTexture(L"BackGround", path + L"BackGround.png");
		app->RegisterTexture(L"Frame", path + L"Frame.png");
		app->RegisterTexture(L"StartPoint", path + L"StartPoint.png");
		app->RegisterTexture(L"GoalPoint", path + L"GoalPoint.png");
		app->RegisterTexture(L"White1x1", path + L"white.png");

		for (int i = 0; i < 3; i++) {
			auto num = to_wstring(i + 1);
			app->RegisterTexture(L"ButtonGuide" + num, path + L"ButtonGuide" + num + L".png");
		}

		for (int i = 1; i < scene->GetMaxStage() + 1; i++) {
			auto stageNum = to_wstring(i);
			app->RegisterTexture(L"Stage" + stageNum + L"_tmb", path + L"thumbnail/Stage" + stageNum + L".png");
		}

		//3Dモデル
		path = dir + L"Models/";
		auto modelMesh = MeshResource::CreateStaticModelMesh(path + L"Enemy/", L"Enemy.bmf");
		app->RegisterResource(L"Enemy", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(path + L"Spikes/", L"Spikes.bmf");
		app->RegisterResource(L"Spikes", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(path + L"Stairs/", L"Stairs.bmf");
		app->RegisterResource(L"Stairs", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(path + L"Battery/", L"Battery.bmf");
		app->RegisterResource(L"Battery", modelMesh);
		modelMesh = MeshResource::CreateStaticModelMesh(path + L"Title/", L"title.bmf");
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
		app->RegisterWav(L"DamageSE", path + L"Damage2.wav");
		app->RegisterWav(L"CursorSE", path + L"Cursor.wav");
		app->RegisterWav(L"DecisionSE", path + L"Decision.wav");
		app->RegisterWav(L"CancelSE", path + L"Cancel.wav");

		app->RegisterWav(L"DoorOpenSE", path + L"DoorOpen.wav");
		app->RegisterWav(L"FallSE", path + L"Fall.wav");
		app->RegisterWav(L"PauseMenuOpenSE", path + L"PauseMenuOpen.wav");
		app->RegisterWav(L"PauseMenuCloseSE", path + L"PauseMenuClose.wav");
		app->RegisterWav(L"WalkSE", path + L"Walk.wav");
		app->RegisterWav(L"IncorrectSE", path + L"Incorrect.wav");

		mtx.lock();
		m_Loaded = true;
		mtx.unlock();
	}

	void LoadStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void LoadStage::OnCreate() {
		auto& app = App::GetApp();
		auto dir = app->GetDataDirWString();
		//コピーライト表示
		auto path = dir + L"Textures/";
		app->RegisterTexture(L"Copyright", path + L"Copyright.png");

		//他のリソースを読み込むスレッドのスタート
		thread LoadThread(LoadResourceFunc);
		//終了までは待たない
		LoadThread.detach();

		CreateViewLight();
		//オブジェクトの配置
		AddGameObject<BGSprite>(L"Copyright");
		AddGameObject<Fade>();

		//タイマーの初期化
		m_timer.Reset();
		m_timer.SetCountTime(m_minTime);
	}

	void LoadStage::OnUpdate() {
		auto fade = GetSharedGameObject<Fade>(L"Fade");
		switch (m_state)
		{
		case State::Loading:
			if (m_Loaded && m_timer.Count()) {
				//リソースのロードが終了&指定の時間が経過したらフェード開始
				fade->FadeOut();
				m_state = State::FadeOut;
			}
			break;
		case State::FadeOut:
			if (!fade->GetFadeActive()) {
				//フェードが完了したらタイトルステージに移行
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
			}
			break;
		}
	}
}
//end basecross