/*!
@file LoadStage.h
@brief リソースのロードのためのステージ
*/

#pragma once
#include "stdafx.h"
#include "TimeCounter.h"

namespace basecross {
	class LoadStage :public Stage {
		enum class State {
			Loading,
			FadeOut
		};

		//最小表示時間
		float m_minTime;
		//カウンター
		TimeCounter m_timer;
		//ステート
		State m_state;

		void CreateViewLight();
		//リソースロード用のスレッド（スタティック関数）
		static void LoadResourceFunc();
		//リソースを読み込んだことを知らせるフラグ（スタティック変数）
		static bool m_Loaded;
		//ミューテックス
		static mutex mtx;
	public:
		LoadStage()
			:Stage(), m_state(State::Loading), m_minTime(2.0f)
		{}
		~LoadStage() {}
		void OnCreate()override;
		void OnUpdate()override;
	};
}
//end basecross