/*!
@file GameStage.h
@brief ゲームステージ
*/

#pragma once
#include "stdafx.h"
#include "TrickArtSystem/TrickArtSystem.h"

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
			CLEAR
		};
	private:
		shared_ptr<TADrawRenderTarget> m_TADrawRenderTarget[2];

		shared_ptr<SoundItem> m_gameBGM;
		//現在のステート
		GameState m_state;
		//ゴールのX座標
		float m_GoalX;
		//ステージナンバー
		int m_stageNum;
		//描画距離
		float m_renderDis;
		//ObjDraw用時間計測用
		float m_drawDelta;
		//State時間計測用
		float m_stateDelta;
		//ひとつ前の値
		int m_beforeValue;
		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		GameStage(int stageNum = 1)
			:Stage(),
			m_state(GameState::FADEIN),
			m_drawDelta(0.0f),
			m_stateDelta(0.0f),
			m_renderDis(25.0f),
			m_beforeValue(0.0f),
			m_GoalX(0.0f),
			m_stageNum(stageNum)
		{
			for (int i = 0; i < 2; i++) {
				m_TADrawRenderTarget[i] = make_shared<TADrawRenderTarget>();
			}
		}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnDestroy()override;

		void ObjDraw(float time);

		bool IsStateClear() {
			switch (m_state)
			{
			case GameState::CLEAR:
				return true;
				break;
			default:
				return false;
				break;
			}
		}

		//現在のステートを取得
		GameState GetState() {
			return m_state;
		}
		//ステートの設定
		void SetState(GameState state);

		float GetGoalX() {
			return m_GoalX;
		}
		void SetGoalX(float x) {
			m_GoalX = x;
		}

		void SetSceneTransition();

		//スタート時のカウントダウン(動作終了するとtrueが返る)
		bool StartCountdown();
		void CreateStageNum();

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

