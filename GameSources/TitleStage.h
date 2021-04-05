/*!
@file TitleStage.h
@brief タイトルステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TitleStage : public Stage {
		shared_ptr<SoundItem> m_titleBGM;
	public:
		// ビューの作成
		void CreateViewLight();

		TitleStage()
			:Stage()
		{}
		// スプライトの作成
		//void CreateSprite();
		// 入力ハンドラー
		//InputHandler<TitleStage> m_Inputhandler;

		void OnCreate() override;
		void OnUpdate() override;
		void OnDestroy()override;
		//void PushB();
	};
}