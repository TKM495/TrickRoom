/*!
@file Player.h
@brief �S�[���܂ł̋�����UI�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross 
{
	class UI_Goalgauge : public GameObject
	{
	public:
		UI_Goalgauge(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
		{}

		void OnCreate() override;
		void OnUpdate() override;
	};
}