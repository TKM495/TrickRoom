/*!
@file MainCamera.cpp
@brief メインカメラなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	MainCamera::MainCamera()
		:m_offset(10.0f, 10.0f, -10.0f),m_Angle(10.0f, -90.0f, -10.0f),bSetPers(false),SetWidth(20.0f),SetHeight(12.5f)
	{

	}

	void MainCamera::OnCreate()
	{

	}

	void MainCamera::OnUpdate()
	{
		//auto& app = App::GetApp(); // アプリケーションオブジェクトを取得
		//auto scene = app->GetScene<Scene>(); // アプリケーションオブジェクトからシーンを取得
		//auto stage = scene->GetActiveStage(); // シーンからステージを取得する
		//auto gameObjects = stage->GetGameObjectVec();
		//std::shared_ptr<Player> player;

		//for (auto gameObject : gameObjects)
		//{
		//	player = dynamic_pointer_cast<Player>(gameObject);
		//	if (player)
		//	{
		//		break;
		//	}
		//}


		//auto TransComp = player->GetComponent<Transform>();
		//auto at = TransComp->GetPosition();

		//SetAt(at);

		//SetEye(at + m_offset);

		

		m_InputHandler.PushHandle(GetThis<MainCamera>());

	}

	Vec3 MainCamera::GetAngle()
	{
		return m_Angle;
	}

	void MainCamera::OnPushB()
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
	
	void MainCamera::OnPushA()
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

		SetEye(at + m_Angle);
	}

}
