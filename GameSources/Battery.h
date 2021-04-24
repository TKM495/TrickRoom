#pragma once
#include "stdafx.h"

namespace basecross {

	class Battery : public StageObject
	{
		float delay;
		float interval;
	public:
		Battery(const shared_ptr<Stage>& stage,
			const wstring& line);

		// : Playerクラスの初期化
		void OnCreate() override; // 初期化用関数をオーバーライドする
		void OnUpdate() override; // 毎フレーム呼ばれる更新用の関数

	protected:
		void ShotBullet();
	};
}
