/*!
@file TitleModel.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TitleModel :public GameObject ,public TrickArtBase{
	public:
		TitleModel(shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}
		void OnCreate()override;
	};

}
//end basecross
