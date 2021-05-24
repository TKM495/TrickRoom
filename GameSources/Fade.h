/*!
@file Fade.h
@brief �t�F�[�h�C���A�A�E�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Fade :public GameObject {
		enum class FadeState {
			Active,
			Stop
		};
		//�t�F�[�h�̏��
		FadeState m_state;
		//�t�F�[�h�̕���(�t�F�[�h�C���Ȃ�-1,�A�E�g�Ȃ�1)
		int m_key;
		//�t�F�[�h�ɂ����鎞��
		float m_fadeTime;
		//���Ԍv���p
		float m_delta;
		//�t�F�[�h�Ɏg�p����F
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

		//���삵�Ă��邩�̃t���O
		bool GetFadeActive() {
			return m_state == FadeState::Active ? true : false;
		}
	};

}
//end basecross
