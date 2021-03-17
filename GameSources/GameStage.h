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
			STAY,
			PLAYING,
			PAUSE,
			CLEAR,
			GAMEOVER
		};
	private:
		//現在のステート
		GameState m_state;
		//死亡ライン
		float m_deathPosY;
		//ビューの作成
		void CreateViewLight();
	public:
		//構築と破棄
		GameStage()
			:Stage(),
			m_state(GameState::STAY),
			m_deathPosY(-5.0f)
		{}
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;

		//現在のステートを取得
		GameState GetState() {
			return m_state;
		}
		//死亡ラインを取得(この座標より下回ったら死亡判定)
		float GetDeathPosY() {
			return m_deathPosY;
		}
	};


}
//end basecross

