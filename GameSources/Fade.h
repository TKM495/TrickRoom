/*!
@file Fade.h
@brief フェードイン、アウト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Fade :public GameObject {
		enum class FadeState {
			Active,
			Stop
		};
		//フェードの状態
		FadeState m_state;
		//フェードの方向(フェードインなら-1,アウトなら1)
		int m_key;
		//フェードにかかる時間
		float m_fadeTime;
		//時間計測用
		float m_delta;
	public:
		Fade(const shared_ptr<Stage>& stage)
			:GameObject(stage),
			m_state(FadeState::Stop),
			m_fadeTime(1.0f),
			m_delta(0.0f),
			m_key(0)
		{}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void FadeIn();
		void FadeOut();

		void SetFadeTime(float time) {
			m_fadeTime = time;
		}

		//動作しているかのフラグ
		bool GetFadeActive() {
			return m_state == FadeState::Active ? true : false;
		}
	};

}
//end basecross
