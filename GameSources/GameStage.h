/*!
@file GameStage.h
@brief �Q�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"
#include "TrickArtSystem/TrickArtSystem.h"
#include "StageObject.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
	public:
		enum class GameState {
			FADEIN,		//�t�F�[�h�C���ҋ@
			STAY,		//�X�^�[�g�O
			PLAYING,	//�v���C��
			PAUSE,		//�|�[�Y��
			CLEAR,		//�N���A��
			FADEOUT		//�t�F�[�h�A�E�g�ҋ@
		};
	private:
		shared_ptr<TADrawRenderTarget> m_TADrawRenderTarget[2];

		shared_ptr<SoundItem> m_gameBGM;
		//UI�̃I�u�W�F�N�g�i�[�p
		vector<shared_ptr<GameObject>> m_uiObjs;
		//���݂̃X�e�[�g
		GameState m_state;
		//�S�[���̈ʒu���
		ObjectPositionForward m_GoalPosForWard;
		//�X�e�[�W�i���o�[
		int m_stageNum;
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
		GameStage(int stageNum = 1)
			:Stage(),
			m_state(GameState::FADEIN),
			m_drawDelta(0.0f),
			m_stateDelta(0.0f),
			m_renderDis(25.0f),
			m_beforeValue(0),
			m_stageNum(stageNum)
		{
			for (int i = 0; i < 2; i++) {
				m_TADrawRenderTarget[i] = make_shared<TADrawRenderTarget>();
			}
		}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnDestroy()override;

		void ObjDraw(float time);

		bool IsStateClear() {
			switch (m_state)
			{
			case GameState::CLEAR:
				return true;
				break;
			default:
				return false;
				break;
			}
		}

		//���݂̃X�e�[�g���擾
		GameState GetState() {
			return m_state;
		}
		//�X�e�[�g�̐ݒ�
		void SetState(GameState state);

		float GetGoalX() {
			return m_GoalPosForWard.origin.x;
		}
		ObjectPositionForward GetGoalPosForward() {
			return m_GoalPosForWard;
		}
		void SetGoalPosForward(ObjectPositionForward opf) {
			m_GoalPosForWard = opf;
		}

		void SetSceneTransition();

		//�X�^�[�g���̃J�E���g�_�E��(����I�������true���Ԃ�)
		bool StartCountdown();
		void CreateStageNum();

		virtual void RenderStage()override;
		shared_ptr<TADrawRenderTarget> GetTADraw(state dir) {
			return m_TADrawRenderTarget[(int)dir];
		}
		shared_ptr<TADrawRenderTarget> GetTADraw(int num) {
			return m_TADrawRenderTarget[num];
		}
	};
}
//end basecross

