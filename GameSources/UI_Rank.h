/*!
@file UI_Rank.h
@brief スコア等のランク
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class UI_Rank :public GameObject {
		enum class Rank {
			S ,A ,B ,C ,D
		};
	public:
		UI_Rank(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		virtual void OnCreate()override;
	};

}
//end basecross
