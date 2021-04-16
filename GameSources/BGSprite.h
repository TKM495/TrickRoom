/*!
@file BGSprite.h
@brief 背景用スプライト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class BGSprite :public GameObject {
		//テクスチャネーム
		wstring m_texName;
	public:
		BGSprite(const shared_ptr<Stage>& stage,
			const wstring& name = L"")
			:GameObject(stage),
			m_texName(name)
		{}

		virtual void OnCreate()override;
		void SetPosition(Vec3 pos) {
			GetComponent<Transform>()->SetPosition(pos);
		}
	};
}
//end basecross
