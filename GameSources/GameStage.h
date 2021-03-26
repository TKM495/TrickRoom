/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
	public:
		enum class GameState {
			STAY,
			PLAYING,
			PAUSE,
			CLEAR,
			GAMEOVER
		};
	private:
		//���݂̃X�e�[�g
		GameState m_state;
		//���S���C��
		float m_deathPosY;
		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		GameStage()
			:Stage(),
			m_state(GameState::PLAYING),
			m_deathPosY(-5.0f)
		{}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;

		//���݂̃X�e�[�g���擾
		GameState GetState() {
			return m_state;
		}
		//���S���C�����擾(���̍��W��艺������玀�S����)
		float GetDeathPosY() {
			return m_deathPosY;
		}
	};


}
//end basecross

