/*!
@file Scene.h
@brief シーン
*/
#pragma once

#include "stdafx.h"

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
		//デバッグステート
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
