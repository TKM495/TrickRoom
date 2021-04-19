/*!
@file TitleStage.h
@brief タイトルステージ
*/

#pragma once
#include "stdafx.h"
#include "TrickArtSystem/TrickArtSystem.h"

namespace basecross {
	class TitleStage : public Stage {
		shared_ptr<SoundItem> m_titleBGM;
		shared_ptr<TADrawRenderTarget> m_TADrawRenderTarget[2];

	public:
		// ビューの作成
		void CreateViewLight();

		TitleStage()
			:Stage()
		{
			for (int i = 0; i < 2; i++) {
				m_TADrawRenderTarget[i] = make_shared<TADrawRenderTarget>();
			}
		}
		// スプライトの作成
		//void CreateSprite();
		// 入力ハンドラー
		//InputHandler<TitleStage> m_Inputhandler;

		void OnCreate() override;
		void OnUpdate() override;
		void OnDestroy()override;
		//void PushB();
		virtual void RenderStage()override;
		shared_ptr<TADrawRenderTarget> GetTADraw(state dir) {
			return m_TADrawRenderTarget[(int)dir];
		}
		shared_ptr<TADrawRenderTarget> GetTADraw(int num) {
			return m_TADrawRenderTarget[num];
		}
	};
}