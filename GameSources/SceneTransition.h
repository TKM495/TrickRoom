/*!
@file SceneTransition.h
@brief �t�F�[�h�C���A�A�E�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SceneTransition :public GameObject {
	public:
		enum class TransDir {
			In,
			Out
		};
	private:
		enum class TransState {
			Active,
			Stop
		};
		//�t�F�[�h�̏��
		TransState m_state;
		//�t�F�[�h�̕���(�t�F�[�h�C���Ȃ�-1,�A�E�g�Ȃ�1)
		int m_key;
		//�t�F�[�h�ɂ����鎞��
		float m_Time;
		//���Ԍv���p
		float m_delta;
		//�ő�T�C�Y
		float m_maxSize;
		float m_start;
		float m_end;
		void SetSize(float size);
		void SetRotation(float deg);
	public:
		SceneTransition(const shared_ptr<Stage>& stage)
			:GameObject(stage),
			m_state(TransState::Stop),
			m_Time(1.0f),
			m_delta(0.0f),
			m_key(0),
			m_maxSize(30.0f),
			m_start(0.0f),
			m_end(0.0f)
		{}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void Play(TransDir dir);

		void SetTransitionTime(float time) {
			m_Time = time;
		}

		float GetTransitionTime() {
			return m_Time;
		}

		//���삵�Ă��邩�̃t���O
		bool GetTransitionActive() {
			return m_state == TransState::Active ? true : false;
		}
	};

}
//end basecross
