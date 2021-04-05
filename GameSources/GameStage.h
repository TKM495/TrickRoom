/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
	public:
		enum class GameState {
			FADEIN,
			STAY,
			PLAYING,
			PAUSE,
			CLEAR,
			GAMEOVER
		};
	private:
		shared_ptr<SoundItem> m_gameBGM;
		//現在のステート
		GameState m_state;
		//スタート地点のオフセット
		float m_startOffset;
		//描画距離
		float m_renderDis;
		//ObjDraw用時間計測用
		float m_drawDelta;
		//State時間計測用
		float m_stateDelta;
		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		GameStage()
			:Stage(),
			m_state(GameState::FADEIN),
			m_drawDelta(0.0f),
			m_stateDelta(0.0f),
			m_renderDis(25.0f),
			m_startOffset(15.0f)
		{}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnDestroy()override;

		void ObjDraw(float time);

		//現在のステートを取得
		GameState GetState() {
			return m_state;
		}
		//ステートの設定
		void SetState(GameState state) {
			if (state == GameState::CLEAR || state == GameState::GAMEOVER) {
				SetSceneTransition();
			}
			m_state = state;
		}

		float GetStartOffset() {
			return m_startOffset;
		}

		void SetSceneTransition();
	};


}
//end basecross

