/*!
@file TimeCounter.h
@brief ���Ԍv���N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TimeCounter {
		float m_delta;
		float m_countTime;
	public:
		TimeCounter()
			:m_delta(0.0f), m_countTime(0.0f)
		{}
		//�����鎞�Ԃ�ݒ肷��֐�
		void SetCountTime(float time) {
			m_countTime = time;
		}
		float GetCountTime() {
			return m_countTime;
		}
		//���݂̎��Ԃ̎擾
		float GetTime() {
			return m_delta;
		}
		//�^�C�}�[�̃��Z�b�g
		void Reset() {
			m_delta = 0.0f;
		}
		//�J�E���g
		bool Count();
		bool Count(float offset);
	};
}
//end basecross