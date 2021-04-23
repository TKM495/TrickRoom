#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void battery::OnCreate()
	{
		auto drawComp = AddComponent<BcPNTStaticDraw>(); // ドロー(描画)コンポーネントを追加
		drawComp->SetMeshResource(L"DEFAULT_CUBE"); // 見た目としてメッシュを設定

		 //デバッグ用の文字列を表示するためのコンポーネントを追加
		auto ssComp = AddComponent<StringSprite>();
		ssComp->SetBackColor(Col4(0.0f, 0.0f, 0.0f, 0.5f)); // 文字列の表示領域の背景色を変更する
		ssComp->SetTextRect(Rect2D<float>(10, 10, 300 + 10, 200 + 10)); // 文字列表示領域のサイズを変更する
		ssComp->SetText(L"Hello world");

		auto transComp = GetComponent<Transform>(); // トランスフォーム(行列変換)コンポーネントを取得
		transComp->SetRotation(0, XMConvertToRadians(0), 0);
	}

	void battery::OnUpdate()
	{
		auto& app = App::GetApp();

		float delta = app->GetElapsedTime();

		auto device = app->GetInputDevice();
		const auto& pad = device.GetControlerVec()[0]; // 0番目のパッドを取得

		auto transComp = GetComponent<Transform>(); // トランスフォーム(行列変換)コンポーネントを取得
		auto pos = transComp->GetPosition(); // 現在の位置座標を取得
		auto quat = transComp->GetQuaternion(); // 回転を取得するときはクォータニオンを用いる
		auto rot = quat.toRotVec(); // 軸ごとの回転に変換する

		// デバッグ用文字列に出力内容を構築する
		wss.str(L"");
		wss << XMConvertToDegrees(rot.x) << ", "
			<< XMConvertToDegrees(rot.y) << ", "
			<< XMConvertToDegrees(rot.z) << std::endl; // 軸ごとの回転角を表示
		wss << L"Bullet count : " << Bullet::getCount();

		// 取得した位置座標をスティックの傾きをもとに更新する
		float h = pad.fThumbLX;
		float v = pad.fThumbLY;
		pos += Vec3(h, 0.0f, v) * 2.0f * delta;

		// 左端の移動制限
		if (pos.x - 0.5f < -5.0f + 1.0f)
		{
			pos.x = -5.0f + 1.0f + 0.5f;
		}

		// 右端の移動制限
		if (pos.x + 0.5f > +5.0f - 1.0f)
		{
			pos.x = +5.0f - 1.0f - 0.5f;
		}

		// 前端の移動制限
		if (pos.z + 0.5f > +5.0f - 1.0f)
		{
			pos.z = +5.0f - 1.0f - 0.5f;
		}

		// 後端の移動制限
		if (pos.z - 0.5f < -5.0f + 1.0f)
		{
			pos.z = -5.0f + 1.0f + 0.5f;
		}

		// スティックの倒れている方向を角度に直す
		if (v != 0 && h != 0) // スティックが倒れていたら・・
		{
			rot.y = atan2f(-v, h) + XM_PIDIV2; // スティックの向きで上書き（進行方向をゼロ度にするために、９０度回転させる）
		}

		// Aボタンが押されたら、弾を発射する
		delay += delta;
		if (delay > 0.5f)
		{
			ShotBullet();
			delay = 0;
		}

		transComp->SetRotation(0, rot.y, 0);
		transComp->SetPosition(pos); // 更新した座標をTransformに設定する
	}

	void battery::OnUpdate2()
	{
		auto ssComp = GetComponent<StringSprite>();
		ssComp->SetText(wss.str());
	}

	// 弾を発射する関数
	void battery::ShotBullet()
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
