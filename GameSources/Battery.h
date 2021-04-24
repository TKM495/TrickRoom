#pragma once
#include "stdafx.h"

namespace basecross {

	class Battery : public StageObject
	{
		float delay;
		float interval;
	public:
		Battery(const shared_ptr<Stage>& stage,
			const wstring& line);

		// : Player�N���X�̏�����
		void OnCreate() override; // �������p�֐����I�[�o�[���C�h����
		void OnUpdate() override; // ���t���[���Ă΂��X�V�p�̊֐�

	protected:
		void ShotBullet();
	};
}
