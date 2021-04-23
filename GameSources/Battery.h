#pragma once
#include "stdafx.h"

namespace basecross {

	class battery : public GameObject // �X�e�[�W�ɒǉ�����I�u�W�F�N�g�͂��ׂ�GameObject�N���X���p��������
	{
		std::wstringstream wss; // �f�o�b�O�p������
		float delay;

	public:
		battery(const std::shared_ptr<Stage>& stage) // GameObject�N���X���p�������N���X�́A�X�e�[�W�I�u�W�F�N�g�ւ̎Q�Ƃ�n����R���X�g���N�^���K�v
			: GameObject(stage), delay(0.0f)
		{
		}

		// : Player�N���X�̏�����
		void OnCreate() override; // �������p�֐����I�[�o�[���C�h����
		void OnUpdate() override; // ���t���[���Ă΂��X�V�p�̊֐�
		void OnUpdate2() override; // �Q��ڂ̍X�V����

	protected:
		void ShotBullet();
	};
}
