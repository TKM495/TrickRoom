/*!
@file Scene.cpp
@brief �V�[������
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	vector<wstring>& Scene::GetStringSpriteData() { return m_stringSpriteWData; }

	DebugState Scene::GetDebugState() { return m_debugState; }
	shared_ptr<SoundItem> Scene::GetTitleBGM() { return m_titleBGM; }
	int Scene::GetStageNum() { return m_stageNum; }
	int Scene::GetMaxStage() { return m_maxStage; }

	wstring Scene::GetNowStageName() { return m_nowStageName; }
	wstring Scene::GetBeforeStageName() { return m_beforeStageName; }

	void Scene::SetTitleBGM(shared_ptr<SoundItem> bgm) {
		m_titleBGM = bgm;
	}
	void Scene::SetStageNum(int num) {
		m_stageNum = num;
	}

	void Scene::OnCreate(){
		try {
			m_debugState = DebugState::None;

			//CSV�t�@�C��
			auto& app = App::GetApp();
			auto dir = app->GetDataDirWString();
			auto path = dir + L"Csv/";
			CsvFile csvFile;
			csvFile.SetFileName(path + L"StringSprite.csv");
			csvFile.ReadCsv();
			m_stringSpriteWData = csvFile.GetCsvVec();

			//�V�[���̏�����
			Col4 Col;
			Col.set(0.5f, 0.5f, 0.7f, 1.0f);
			SetClearColor(Col);
			m_nowStageName = L"Startup";
			//�N�����̃X�e�[�W
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToLoadStage");
		}
		catch (...) {
			throw;
		}
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		m_beforeStageName = m_nowStageName;
		m_nowStageName = event->m_MsgStr;
		//���\�[�X�ǂݍ��ݗp�̃X�e�[�W
		if (event->m_MsgStr == L"ToLoadStage") {
			ResetActiveStage<LoadStage>();
		}
		//�^�C�g��
		else if (event->m_MsgStr == L"ToTitleStage") {
			ResetActiveStage<TitleStage>();
		}
		//�X�e�[�W�Z���N�g
		else if (event->m_MsgStr == L"ToSelectStage") {
			ResetActiveStage<SelectStage>();
		}
		//�Q�[���{��
		else if (event->m_MsgStr == L"ToGameStage") {
			ResetActiveStage<GameStage>(GetStageNum());
		}
		//���U���g�X�e�[�W
		else if (event->m_MsgStr == L"ToResultStage") {
			ResetActiveStage<ResultStage>();
		}
		//�Q�[���I��
		else if (event->m_MsgStr == L"ToExit") {
			PostQuitMessage(0);
		}
	}

}
//end basecross
