/*!
@file UI_Rank.h
@brief スコア等のランク
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum class Rank {
		S, A, B, MAX
	};

	class UI_Rank :public GameObject {
		Rank m_rank;
		Vec2 m_originalSize;
	public:
		UI_Rank(const shared_ptr<Stage>& stage,
			const Rank& rank)
			:GameObject(stage),
			m_rank(rank),
			m_originalSize(Vec2(300.0f))
		{}

		virtual void OnCreate()override;

		void SetSize(float size);
		void SetPosition(Vec2 pos);
	};
}
//end basecross
