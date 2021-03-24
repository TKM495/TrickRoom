/*!
@file Scene.h
@brief �V�[��
*/
#pragma once

#include "stdafx.h"

namespace basecross{
	enum class DebugState {
		None,
		Debug
	};

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase{
		//�X�v���C�g�pCSV�f�[�^
		vector<wstring> m_spriteWData;
		//�f�o�b�O�X�e�[�g
		DebugState m_debugState;

	public:
		Scene() :SceneBase(),
			m_debugState(DebugState::None)
		{}
		virtual ~Scene() {}
		virtual void OnCreate() override;
		virtual void OnEvent(const shared_ptr<Event>& event) override;

		vector<wstring>& GetSpriteData() {
			return m_spriteWData;
		}

		DebugState GetDebugState() {
			return m_debugState;
		}

	};

}

//end basecross
