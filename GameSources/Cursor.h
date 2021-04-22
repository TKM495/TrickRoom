/*!
@file Cursor.h
@brief ���j���[�p�̃J�[�\���N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Cursor :public GameObject {
		//�F
		Col4 m_color;
		//�ő哧�ߗ�
		float m_max;
		//�ŏ����ߗ�
		float m_min;
		//���x
		float m_rate;
		//���Ԍv���p
		float m_delta;
		//�J�[�\���e�N�X�`��
		wstring m_name;
	public:
		Cursor(const shared_ptr<Stage>& stage,
			const wstring& name)
			:GameObject(stage),
			m_name(name),m_max(0.3f), m_min(0.2f), m_rate(6.0f), m_delta(0.0f)
		{}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void SetValue(float max, float min) {
			m_max = max;
			m_min = min;
		}

		void SetRate(float rate) {
			m_rate = rate;
		}
	};

}
//end basecross
