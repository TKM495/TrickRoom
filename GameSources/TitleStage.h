/*!
@file TitleStage.h
@brief �^�C�g���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TitleStage : public Stage {
		shared_ptr<SoundItem> m_titleBGM;
	public:
		// �r���[�̍쐬
		void CreateViewLight();

		TitleStage()
			:Stage()
		{}
		// �X�v���C�g�̍쐬
		//void CreateSprite();
		// ���̓n���h���[
		//InputHandler<TitleStage> m_Inputhandler;

		void OnCreate() override;
		void OnUpdate() override;
		void OnDestroy()override;
		//void PushB();
	};
}