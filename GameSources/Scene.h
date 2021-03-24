/*!
@file Scene.h
@brief シーン
*/
#pragma once

#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase{
		//スプライト用CSVデータ
		vector<wstring> m_spriteWData;
		//オブジェクト用CSVデータ
		vector<wstring> m_objectWData;

	public:
		Scene() :SceneBase(){}
		virtual ~Scene() {}
		virtual void OnCreate() override;
		virtual void OnEvent(const shared_ptr<Event>& event) override;

		vector<wstring>& GetSpriteData() {
			return m_spriteWData;
		}
		vector<wstring>& GetObjectData() {
			return m_objectWData;
		}
	};

}

//end basecross
