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
		int m_num;
	public:
		Scene() :SceneBase(),
			m_debugState(DebugState::None),
			m_num(1)
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

		void SetNum(int _num) {
			m_num = _num;
		}
		int GetNum() {
			return m_num;
		}
	};

}

//end basecross
