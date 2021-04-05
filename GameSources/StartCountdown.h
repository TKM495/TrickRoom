/*!
@file StartCountdown.h
@brief �X�^�[�g���̃J�E���g�_�E�����o
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class StartCountdown :public GameObject {
		//�����I�u�W�F�N�g
		shared_ptr<Numbers> m_numObjs[3];
		//�����I�u�W�F�N�g
		shared_ptr<StringSprite2> m_strObj;
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

	};

}
//end basecross
