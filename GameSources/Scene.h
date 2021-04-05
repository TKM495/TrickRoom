/*!
@file Scene.h
@brief �V�[��
*/
#pragma once

#include "stdafx.h"
#include "Result.h"

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
		//�摜�pCSV�f�[�^
		vector<wstring> m_pictureWData;
		//�X�R�A�f�[�^
		ScoreData m_scoreData;
		//�f�o�b�O�X�e�[�g
		DebugState m_debugState;
	public:
		Scene() :SceneBase()
		{}
		virtual ~Scene() {}
		virtual void OnCreate() override;
		virtual void OnEvent(const shared_ptr<Event>& event) override;

		vector<wstring>& GetSpriteData() {
			return m_spriteWData;
		}

		vector<wstring>& GetPictureData() {
			return m_pictureWData;
		}

		DebugState GetDebugState() {
			return m_debugState;
		}

		void SetScoreData(ScoreData data) {
			m_scoreData = data;
		}

		ScoreData GetScoreData() {
			return m_scoreData;
		}
	};

}

//end basecross
