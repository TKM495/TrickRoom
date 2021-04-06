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
			FADEIN,
			STAY,
			PLAYING,
			PAUSE,
			CLEAR,
			GAMEOVER
		};
	private:
		shared_ptr<SoundItem> m_gameBGM;
		//���݂̃X�e�[�g
		GameState m_state;
		//�X�^�[�g�n�_�̃I�t�Z�b�g
		float m_startOffset;
		//�`�拗��
		float m_renderDis;
		//ObjDraw�p���Ԍv���p
		float m_drawDelta;
		//State���Ԍv���p
		float m_stateDelta;
		//�ЂƂO�̒l
		int m_beforeValue;
		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		GameStage()
			:Stage(),
			m_state(GameState::FADEIN),
			m_drawDelta(0.0f),
			m_stateDelta(0.0f),
			m_renderDis(25.0f),
			m_startOffset(20.0f),
			m_beforeValue(0.0f)
		{}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnDestroy()override;

		void ObjDraw(float time);

		//���݂̃X�e�[�g���擾
		GameState GetState() {
			return m_state;
		}
		//�X�e�[�g�̐ݒ�
		void SetState(GameState state);

		float GetStartOffset() {
			return m_startOffset;
		}

		void SetSceneTransition();

		//�X�^�[�g���̃J�E���g�_�E��(����I�������true���Ԃ�)
		bool StartCountdown();
	};
}
//end basecross

