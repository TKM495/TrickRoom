/*!
@file MainCamera.cpp
@brief メインカメラなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	MainCamera::MainCamera()
		:m_offset(0.0f, 5.0f, -5.0f)
	{

	}

	void MainCamera::OnCreate()
	{

	}

	void MainCamera::OnUpdate()
	{
		auto& app = App::GetApp(); // アプリケーションオブジェクトを取得
		auto scene = app->GetScene<Scene>(); // アプリケーションオブジェクトからシーンを取得
		auto stage = scene->GetActiveStage(); // シーンからステージを取得する
		auto gameObjects = stage->GetGameObjectVec();
		std::shared_ptr<Player> player;

		for (auto gameObject : gameObjects)
		{
			player = dynamic_pointer_cast<Player>(gameObject);
			if (player)
			{
				break;
			}
		}


		auto TransComp = player->GetComponent<Transform>();
		auto at = TransComp->GetPosition();

		SetAt(at);

		SetEye(at + m_offset);
	}

	
}
