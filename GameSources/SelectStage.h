/*!
@file SelectStage.h
@brief セレクトステージ(ステージセレクト画面)
*/

#pragma once
#include "stdafx.h"
#include "ImageSprite.h"
#include "SelectStageMenu.h"
#include "TrickArtSystem/TrickArtSystem.h"

namespace basecross {
	class SelectStage : public Stage {
		shared_ptr<SoundItem> m_selectBGM;
		shared_ptr<SelectStageMenu> m_menu;
		shared_ptr<ImageSprite> m_arrows[2];
		Vec2 m_arrowsPos[2];
		float m_delta;
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
