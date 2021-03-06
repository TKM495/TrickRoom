/*!
@file ResultStage.h
@brief 結果画面
*/

#pragma once
#include "stdafx.h"
#include "Result.h"

namespace basecross {
	class ResultStage : public Stage {
	public:
		ResultStage()
			:Stage()
		{}

		// ビューの作成
		void CreateViewLight();

		void OnCreate() override;
		void OnUpdate() override;
	};

}
//end basecross
