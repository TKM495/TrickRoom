/*!
@file FadeComponent.h
@brief �t�F�[�h�R���|�[�l���g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class FadeComponent :public Component {
		//�t�F�[�h�̕���
		enum class Direction {
			FadeIn,
			FadeOut
		};
		//�t�F�[�h�̕���
		Direction m_dir;
		//�t�F�[�h�����쒆���ǂ���
		bool m_bActive;
		//�t�F�[�h�ɂ����鎞��
		float m_fadeTime;
		//���Ԍv���p
		float m_delta;
		//�F
		Col4 m_color;
	public:
		FadeComponent(const shared_ptr<GameObject>& objPtr)
			:Component(objPtr),
			m_dir(Direction::FadeIn),
			m_bActive(false),
			m_fadeTime(1.0f),
			m_delta(0.0f),
			m_color(Col4(0.0f))
		{}
		virtual void OnUpdate()override;
		virtual void OnDraw()override{}

		void SetFadeColor(Col4 color) {
			m_color = color;
		}

		void FadeIn();
		void FadeOut();

		void SetFadeTime(float time) {
			m_fadeTime = time;
		}

		float GetFadeTime() {
			return m_fadeTime;
		}

		//���삵�Ă��邩�̃t���O
		bool IsFadeActive() {
			return m_bActive;
		}
	};

}
//end basecross
