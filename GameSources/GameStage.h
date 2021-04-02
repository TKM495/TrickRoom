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
		//�`�拗��
		float m_renderDis;
		//ObjDraw�p���Ԍv���p
		float m_drawDelta;
		//State���Ԍv���p
		float m_stateDelta;
		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		GameStage()
			:Stage(),
			m_state(GameState::STAY),
			m_deathPosY(-5.0f),
			m_drawDelta(0.0f),
			m_stateDelta(0.0f),
			m_renderDis(25.0f)
		{}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void ObjDraw(float time);

		//���݂̃X�e�[�g���擾
		GameState GetState() {
			return m_state;
		}
		//�X�e�[�g�̐ݒ�
		void SetState(GameState state) {
			if (state == GameState::CLEAR || state == GameState::GAMEOVER) {
				SetSceneTransition();
			}
			m_state = state;
		}
		//���S���C�����擾(���̍��W��艺������玀�S����)
		float GetDeathPosY() {
			return m_deathPosY;
		}

		void SetSceneTransition();
	};


}
//end basecross

