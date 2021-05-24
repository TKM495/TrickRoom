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
		//フェードに使用する色
		Col4 m_color;
	public:
		Fade(const shared_ptr<Stage>& stage)
			:GameObject(stage),
			m_state(FadeState::Stop),
			m_fadeTime(1.0f),
			m_delta(0.0f),
			m_key(0),
			m_color(Col4(0.0f, 0.0f, 0.0f, 1.0f))
		{}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void FadeIn();
		void FadeOut();

		void SetFadeTime(float time) {
			m_fadeTime = time;
		}

		float GetFadeTime() {
			return m_fadeTime;
		}

		void SetFadeColor(Col4 color) {
			m_color = color;
		}

		Col4 GetFadeColor() {
			return m_color;
		}

		//動作しているかのフラグ
		bool GetFadeActive() {
			return m_state == FadeState::Active ? true : false;
		}
	};

}
//end basecross
