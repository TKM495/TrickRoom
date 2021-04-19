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
		shared_ptr<TADrawRenderTarget> m_TADrawRenderTarget[2];

	public:
		SelectStage()
			:Stage()
		{
			for (int i = 0; i < 2; i++) {
				m_TADrawRenderTarget[i] = make_shared<TADrawRenderTarget>();
			}
		}
		// ビューの作成
		void CreateViewLight();

		void OnCreate() override;
		void OnUpdate() override;
		void OnDestroy()override;
		virtual void RenderStage()override;
		shared_ptr<TADrawRenderTarget> GetTADraw(state dir) {
			return m_TADrawRenderTarget[(int)dir];
		}
		shared_ptr<TADrawRenderTarget> GetTADraw(int num) {
			return m_TADrawRenderTarget[num];
		}
	};
}
//end basecross
