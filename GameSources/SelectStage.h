/*!
@file SelectStage.h
@brief �Z���N�g�X�e�[�W(�X�e�[�W�Z���N�g���)
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SelectStage : public Stage {
	public:
		// �r���[�̍쐬
		void CreateViewLight();

		void OnCreate() override;
		void OnUpdate() override;
	};
}
//end basecross