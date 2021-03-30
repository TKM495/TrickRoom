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
		Vec3 m_position;
	public:
		Scene() :SceneBase(),
			m_position(Vec3(48.0f, 0.5f, -4.0f))
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

		Vec3 GetPos() {
			return m_position;
		}

		void SetPos(Vec3 pos) {
			m_position = pos;
		}

	};

}

//end basecross
