/*!
@file UI_FPS.h
@brief フレームレートUI
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class UI_FPS :public GameObject {
	public:
		UI_FPS(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{
		}
		void OnCreate()override;
		void OnUpdate()override;
	};
}
//end basecross
