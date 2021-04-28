/*!
@file Scene.h
@brief シーン
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
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase{
		//文字スプライト用CSVデータ
		vector<wstring> m_stringSpriteWData;
		//画像スプライト用CSVデータ
		vector<wstring> m_imageSpriteWData;
		//画像用CSVデータ
		vector<wstring> m_pictureWData;
		//各ステージに置けるランクの基準用CSVデータ
		vector<wstring> m_stageScoreWData;
		//スコアデータ
		ScoreData m_scoreData;
		//タイトルBGM
		shared_ptr<SoundItem> m_titleBGM;
		//ロードするステージ番号
		int m_stageNum;
		//最大ステージ数
		int m_maxStage;
		//デバッグステート
		DebugState m_debugState;
		//現在のステージ名
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
