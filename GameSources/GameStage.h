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
		GameState m_state;
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

		GameState GetState();
		float GetDeathPosY();
	};


}
//end basecross

