/*!
@file BGSprite.h
@brief 背景用スプライト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class BGEffectSprite :public GameObject {
		//テクスチャネーム
		wstring m_texName;
		//色
		Col4 m_color;
	public:
		BGEffectSprite(const shared_ptr<Stage>& stage,
			const wstring& name = L"")
			:GameObject(stage),
			m_texName(name),
			m_color(Col4(1.0f))
		{}

		BGEffectSprite(const shared_ptr<Stage>& stage,
			const Col4& color)
			:GameObject(stage),
			m_texName(L""),
			m_color(color)
		{}

		virtual void OnCreate()override;
	};
}
//end basecross
