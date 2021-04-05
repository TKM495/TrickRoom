/*!
@file StartCountdown.h
@brief �X�^�[�g���̃J�E���g�_�E�����o
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class StartCountdown :public GameObject {
		//�Q�[���I�u�W�F�N�g�z��(4�Ȃ̂�1�`3�ƃX�^�[�g)
		shared_ptr<GameObject> m_objs[4];
		//���Ԍv���p
		float m_delta;
		//�ЂƂO�̒l
		int m_beforeValue;
		//Update()�̂Ȃ��Ŋ֐�����񂾂����s���邽�߂̃t���O
		bool m_bOneTime;
	public:
		StartCountdown(const shared_ptr<Stage>& stage)
			:GameObject(stage),
			m_delta(4.0f),
			m_bOneTime(false)
		{}

		void OnCreate()override;
		void OnUpdate()override;

		//�J�E���g�X�^�[�g
		void Start() {
			SetUpdateActive(true);
		}
	};

}
//end basecross
