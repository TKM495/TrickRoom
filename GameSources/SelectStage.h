/*!
@file SelectStage.h
@brief セレクトステージ(ステージセレクト画面)
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SelectStage : public Stage {
	public:
		// ビューの作成
		void CreateViewLight();

		void OnCreate() override;
		void OnUpdate() override;
	};
}
//end basecross
