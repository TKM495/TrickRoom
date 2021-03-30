/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<MainCamera>();
		PtrView->SetCamera(PtrCamera);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			AddGameObject<Debug>();

			//AddGameObject<Timer>();
			AddGameObject<UI_HP>();
			AddGameObject<UI_Crystal>();

			//ゲームオブジェクトビルダー
			GameObjecttCSVBuilder builder;
			//ゲームオブジェクトの登録
			builder.Register<Player>(L"Player");
			builder.Register<Plane>(L"Plane");
			builder.Register<Pillar>(L"Pillar");
			builder.Register<Block>(L"Block");
			builder.Register<BlockArt>(L"BlockArt");
			builder.Register<Enemy>(L"Enemy");
			builder.Register<EnemyArt>(L"EnemyArt");
			builder.Register<Spikes>(L"Spikes");
			builder.Register<SpikesArt>(L"SpikesArt");
			builder.Register<Stairs>(L"Stairs");
			builder.Register<StairsArt>(L"StairsArt");
			builder.Register<FloorArt>(L"FloorArt");
			builder.Register<PoleArt>(L"PoleArt");
			builder.Register<Crystal>(L"Crystal");
			//builder.Register<FloorGenerator>(L"FloorGenerator");

			auto& app = App::GetApp();
			auto dir = app->GetDataDirWString();
			auto path = dir + L"Csv/Object.csv";
			//auto& app = App::GetApp();
			//auto dir = app->GetDataDirWString();
			//auto path = dir + L"Csv/Object";
			//path += scene->GetNum();
			//path += L".csv";

			builder.Build(GetThis<Stage>(), path);

			//StageObjectのタグを持つオブジェクトをStageParentの子にする
			auto stagePar = AddGameObject<StageParent>();
			vector<shared_ptr<GameObject>> stageObjs;
			GetUsedTagObjectVec(L"StageObject", stageObjs);
			for (auto& obj : stageObjs) {
				obj->GetComponent<Transform>()->SetParent(stagePar);
			}
			stagePar->GetComponent<Transform>()->
				SetPosition(Vec3(-20.0f, 0.0f, 0.0f));

			AddGameObject<Fade>()->FadeIn();
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate() {
		auto delta = App::GetApp()->GetElapsedTime();
		switch (m_state)
		{
		case GameState::STAY:


			break;
		case GameState::PLAYING:
			break;
		case GameState::PAUSE:
			break;
		case GameState::CLEAR:
			break;
		case GameState::GAMEOVER:
			break;
		default:
			break;
		}

		m_StateDelta += delta;
		ObjDraw(0.1f);
	}

	void GameStage::ObjDraw(float time) {
		auto delta = App::GetApp()->GetElapsedTime();
		m_drawDelta += delta;
		if (m_drawDelta <= time) {
			return;
		}
		m_drawDelta = 0.0f;

		auto parent = GetSharedGameObject<StageParent>(L"StageParent");
		auto parentPos = parent->GetComponent<Transform>()->GetPosition();

		vector<shared_ptr<GameObject>> stageObjs;
		GetUsedTagObjectVec(L"StageObject", stageObjs);
		auto camera = dynamic_pointer_cast<MainCamera>(GetView()->GetTargetCamera());
		auto playerPos = camera->GetAt();
		for (auto& obj : stageObjs) {
			if (obj->FindTag(L"Plane") || obj->FindNumTag(-1)) {
				continue;
			}

			auto pos = obj->GetComponent<Transform>()->GetPosition();
			pos += parentPos;
			auto dir = playerPos - pos;
			if (dir.lengthSqr() > m_renderDis * m_renderDis) {
				obj->SetDrawActive(false);
				obj->SetUpdateActive(false);
			}
			else {
				obj->SetDrawActive(true);
				obj->SetUpdateActive(true);
			}
		}
	}

}
//end basecross
