#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Battery::Battery(const shared_ptr<Stage>& stage,
		const wstring& line)
		:StageObject(stage), delay(0.0f)
	{
		vector<wstring> tokens;
		Util::WStrToTokenVector(tokens, line, L',');
		m_position = Vec3(
			(float)_wtof(tokens[1].c_str()),
			(float)_wtof(tokens[2].c_str()),
			(float)_wtof(tokens[3].c_str())
		);
		m_scale = Vec3(
			(float)_wtof(tokens[4].c_str()),
			(float)_wtof(tokens[5].c_str()),
			(float)_wtof(tokens[6].c_str())
		);
		m_rotation = Vec3(
			XMConvertToRadians((float)_wtof(tokens[7].c_str())),
			XMConvertToRadians((float)_wtof(tokens[8].c_str())),
			XMConvertToRadians((float)_wtof(tokens[9].c_str()))
		);
		interval = (float)_wtof(tokens[10].c_str());
	}

	void Battery::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>(); // ドロー(描画)コンポーネントを追加
		drawComp->SetMeshResource(L"DEFAULT_CUBE"); // 見た目としてメッシュを設定
		auto col = AddComponent<CollisionObb>();
		col->SetFixed(true);
		StageObject::OnCreate();
		AddTag(L"Battery");
	}

	void Battery::OnUpdate()
	{
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime();
		auto state = dynamic_pointer_cast<GameStage>(GetStage())->GetState();
		switch (state)
		{
		default:
			delay += delta;
			break;
		case basecross::GameStage::GameState::PAUSE:
			break;
		}
		if (delay > interval)
		{
			ShotBullet();
			delay = 0;
		}
	}

	// 弾を発射する関数
	void Battery::ShotBullet()
	{
		// プレイヤー自身のトランスフォームを取得する
		auto playerTrans = GetComponent<Transform>();
		auto playerPos = playerTrans->GetPosition();
		auto playerQuat = playerTrans->GetQuaternion();

		auto stage = GetStage(); // Playerオブジェクトが所属するステージを取得する
		auto bullet = stage->AddGameObject<Bullet>(); // そのステージに弾を追加する
		auto bulletTrans = bullet->GetComponent<Transform>();
		bulletTrans->SetPosition(playerPos); // プレイヤーの座標に合わせる
		bulletTrans->SetQuaternion(playerQuat); // プレイヤーの方向(姿勢)に合わせる
	}
}
