/*!
@file SelectStage.h
@brief �Z���N�g�X�e�[�W(�X�e�[�W�Z���N�g���)
*/

#pragma once
#include "stdafx.h"
#include "TrickArtSystem/TrickArtSystem.h"

namespace basecross {
	class SelectStage : public Stage {
		shared_ptr<SoundItem> m_selectBGM;
	public:
		SelectStage()
			:Stage()
		{}
		// �r���[�̍쐬
		void CreateViewLight();

		void OnCreate() override;
		void OnUpdate() override;
		void OnDestroy()override;
	};
}
//end basecross
