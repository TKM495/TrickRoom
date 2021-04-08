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
		//スコアデータ
		ScoreData m_scoreData;
		//デバッグステート
		DebugState m_debugState;
	public:
		Scene() :SceneBase()
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
