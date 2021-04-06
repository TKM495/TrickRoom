/*!
@file Player.h
@brief ƒS[ƒ‹‚Ü‚Å‚Ì‹——£‚ÌUI‚È‚Ç
*/

#pragma once
#include "stdafx.h"

namespace basecross
{
	class UI_Goalgauge : public GameObject
	{
		bool bActive;
	public:
		UI_Goalgauge(const std::shared_ptr<Stage>& stage) :
			GameObject(stage), bActive(false)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		void FadeIn();
	};
}