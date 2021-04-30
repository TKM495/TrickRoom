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
	class Scene : public SceneBase {
		//文字スプライト用CSVデータ
		vector<wstring> m_stringSpriteWData;
		//画像スプライト用CSVデータ
		vector<wstring> m_imageSpriteWData;
		//画像用CSVデータ
		vector<wstring> m_pictureWData;
		//各ステージに置けるランクの基準用CSVデータ
		vector<wstring> m_stageScoreWData;
		//タイトルBGM
		shared_ptr<SoundItem> m_titleBGM;
		//ロードするステージ番号
		int m_stageNum;
		//最大ステージ数
		int m_maxStage;
		//デバッグステート
		DebugState m_debugState;
		//現在のステージ(シーン)名
		wstring m_nowStageName;
		//以前のステージ(シーン)名
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
