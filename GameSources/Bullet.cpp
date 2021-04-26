#include "stdafx.h"
#include "Project.h"

namespace basecross {
	int Bullet::count = 0;

	void Bullet::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");

		auto transComp = GetComponent<Transform>();
		float scale = 0.5f;
		transComp->SetScale(scale, scale, scale);

		AddComponent<CollisionSphere>();
		AddTag(L"damage");
		AddTag(L"Bullet");
	}

	void Bullet::OnUpdate()
	{
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime(); // デルタ時間（フレームタイム）
											 // （前のフレームを処理するのにかかった時間、
											 //   つまり前のフレームからの経過時間）
		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();
		auto forward = transComp->GetForword(); // オブジェクトの正面を表す単位ベクトル
		auto state = dynamic_pointer_cast<GameStage>(GetStage())->GetState();
		switch (state)
		{
		default:
			pos += forward * 10.0f * delta; // 前方に秒速10.0移動する
			break;
		case basecross::GameStage::GameState::PAUSE:
			break;
		}

		transComp->SetPosition(pos);
	}

	void Bullet::OnCollisionEnter(shared_ptr<GameObject>& other) {
		if (!other->FindTag(L"Battery")) {
			// 消す
			GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());
		}
	}
}