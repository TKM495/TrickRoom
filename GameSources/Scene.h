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
		//スプライト用CSVデータ
		vector<wstring> m_spriteWData;
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
