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
	class Scene : public SceneBase {
		//�����X�v���C�g�pCSV�f�[�^
		vector<wstring> m_stringSpriteWData;
		//�摜�X�v���C�g�pCSV�f�[�^
		vector<wstring> m_imageSpriteWData;
		//�摜�pCSV�f�[�^
		vector<wstring> m_pictureWData;
		//�e�X�e�[�W�ɒu���郉���N�̊�pCSV�f�[�^
		vector<wstring> m_stageScoreWData;
		//�^�C�g��BGM
		shared_ptr<SoundItem> m_titleBGM;
		//���[�h����X�e�[�W�ԍ�
		int m_stageNum;
		//�ő�X�e�[�W��
		int m_maxStage;
		//�f�o�b�O�X�e�[�g
		DebugState m_debugState;
		//���݂̃X�e�[�W(�V�[��)��
		wstring m_nowStageName;
		//�ȑO�̃X�e�[�W(�V�[��)��
		wstring m_beforeStageName;
	public:
		Scene() :SceneBase(),
			m_stageNum(1),
			m_maxStage(10)
		{}
		virtual ~Scene() {}
		virtual void OnCreate() override;
		virtual void OnEvent(const shared_ptr<Event>& event) override;

		vector<wstring>& GetStringSpriteData();
		vector<wstring>& GetImageSpriteData();
		vector<wstring>& GetPictureData();
		vector<wstring>& GetStageScoreData();

		DebugState GetDebugState();
		shared_ptr<SoundItem> GetTitleBGM();
		void SetTitleBGM(shared_ptr<SoundItem> bgm);
		void SetStageNum(int num);
		int GetStageNum();
		int GetMaxStage();

		wstring GetNowStageName();
		wstring GetBeforeStageName();
	};
}

//end basecross
