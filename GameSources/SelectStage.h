/*!
@file SelectStage.h
@brief セレクトステージ(ステージセレクト画面)
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SelectStage : public Stage {
		shared_ptr<SoundItem> m_selectBGM;
	public:
		// ビューの作成
		void CreateViewLight();

		void OnCreate() override;
		void OnUpdate() override;
		void OnDestroy()override;

	};
}
//end basecross
