/*!
@file SelectStage.h
@brief セレクトステージ(ステージセレクト画面)
*/

#pragma once
#include "stdafx.h"
#include "TrickArtSystem/TrickArtSystem.h"

namespace basecross {
	class SelectStage : public Stage {
		shared_ptr<SoundItem> m_selectBGM;
	public:
		SelectStage()
			:Stage()
		{}
		// ビューの作成
		void CreateViewLight();

		void OnCreate() override;
		void OnUpdate() override;
		void OnDestroy()override;
	};
}
//end basecross
