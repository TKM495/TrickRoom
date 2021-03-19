/*!
@file TitleStage.h
@brief タイトルステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TitleStage : public Stage {
		// ビューの作成
		void CreateViewLight();
		// スプライトの作成
		//void CreateSprite();
		// 入力ハンドラー
		InputHandler<TitleStage> m_Inputhandler;

		void OnCreate() override;
		void OnUpdate() override;

		void PushB();
	};
}