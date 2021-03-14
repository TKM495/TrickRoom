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
		GameState m_state;
		float m_deathPosY;

		//�r���[�̍쐬
		void CreateViewLight();
	public:
		//�\�z�Ɣj��
		GameStage()
			:Stage(),
			m_state(GameState::STAY),
			m_deathPosY(-5.0f)
		{}
		virtual ~GameStage() {}
		//������
		virtual void OnCreate()override;

		GameState GetState();
		float GetDeathPosY();
	};


}
//end basecross

