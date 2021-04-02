/*!
@file ResultStage.h
@brief Œ‹‰Ê‰æ–Ê
*/

#pragma once
#include "stdafx.h"
#include "Result.h"

namespace basecross {
	class ResultStage : public Stage {
	public:
		ResultStage()
			:Stage()
		{}

		// ƒrƒ…[‚Ìì¬
		void CreateViewLight();

		void OnCreate() override;
		void OnUpdate() override;

		//void PushB();
	};

}
//end basecross
