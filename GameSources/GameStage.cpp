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
