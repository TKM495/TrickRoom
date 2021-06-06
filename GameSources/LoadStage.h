/*!
@file LoadStage.h
@brief ���\�[�X�̃��[�h�̂��߂̃X�e�[�W
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

		//�ŏ��\������
		float m_minTime;
		//�J�E���^�[
		TimeCounter m_timer;
		//�X�e�[�g
		State m_state;

		void CreateViewLight();
		//���\�[�X���[�h�p�̃X���b�h�i�X�^�e�B�b�N�֐��j
		static void LoadResourceFunc();
		//���\�[�X��ǂݍ��񂾂��Ƃ�m�点��t���O�i�X�^�e�B�b�N�ϐ��j
		static bool m_Loaded;
		//�~���[�e�b�N�X
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