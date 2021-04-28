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
		//�����X�v���C�g�pCSV�f�[�^
		vector<wstring> m_stringSpriteWData;
		//�摜�X�v���C�g�pCSV�f�[�^
		vector<wstring> m_imageSpriteWData;
		//�摜�pCSV�f�[�^
		vector<wstring> m_pictureWData;
		//�e�X�e�[�W�ɒu���郉���N�̊�pCSV�f�[�^
		vector<wstring> m_stageScoreWData;
		//�X�R�A�f�[�^
		ScoreData m_scoreData;
		//�^�C�g��BGM
		shared_ptr<SoundItem> m_titleBGM;
		//���[�h����X�e�[�W�ԍ�
		int m_stageNum;
		//�ő�X�e�[�W��
		int m_maxStage;
		//�f�o�b�O�X�e�[�g
		DebugState m_debugState;
		//���݂̃X�e�[�W��
		wstring m_nowStageName;
	public:
		Scene() :SceneBase(),
			m_stageNum(1),
			m_maxStage(10)
		{}
		virtual ~Scene() {}
		virtual void OnCreate() override;
		virtual void OnEvent(const shared_ptr<Event>& event) override;

		vector<wstring>& GetStringSpriteData() {
			return m_stringSpriteWData;
		}

		vector<wstring>& GetImageSpriteData() {
			return m_imageSpriteWData;
		}

		vector<wstring>& GetPictureData() {
			return m_pictureWData;
		}

		vector<wstring>& GetStageScoreData() {
			return m_stageScoreWData;
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

		void SetTitleBGM(shared_ptr<SoundItem> bgm) {
			m_titleBGM = bgm;
		}

		shared_ptr<SoundItem> GetTitleBGM() {
			return m_titleBGM;
		}

		void SetStageNum(int num) {
			m_stageNum = num;
		}

		int GetStageNum() {
			return m_stageNum;
		}

		int GetMaxStage() {
			return m_maxStage;
		}

		wstring GetNowStageName() {
			return m_nowStageName;
		}
	};

}

//end basecross
