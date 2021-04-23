#pragma once
#include "stdafx.h"

namespace basecross {

	class battery : public GameObject // ステージに追加するオブジェクトはすべてGameObjectクラスを継承させる
	{
		std::wstringstream wss; // デバッグ用文字列
		float delay;

	public:
		battery(const std::shared_ptr<Stage>& stage) // GameObjectクラスを継承したクラスは、ステージオブジェクトへの参照を渡せるコンストラクタが必要
			: GameObject(stage), delay(0.0f)
		{
		}

		// : Playerクラスの初期化
		void OnCreate() override; // 初期化用関数をオーバーライドする
		void OnUpdate() override; // 毎フレーム呼ばれる更新用の関数
		void OnUpdate2() override; // ２回目の更新処理

	protected:
		void ShotBullet();
	};
}
