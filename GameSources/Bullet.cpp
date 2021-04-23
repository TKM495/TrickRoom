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

		pos += forward * 10.0f * delta; // 前方に秒速10.0移動する
		if (pos.x > 5.0f - 1.0f || pos.x < -5.0f + 1.0f ||
			pos.z > 5.0f - 1.0f || pos.z < -5.0f + 1.0f)
		{
			// 消す
			GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());
		}

		transComp->SetPosition(pos);
	}
}