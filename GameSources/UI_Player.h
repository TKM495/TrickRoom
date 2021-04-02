/*!
@file UI_Player.h
@brief �����v���C���[��UI�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross
{
	class UI_Player : public GameObject
	{
	public:
		UI_Player(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
		{}

		void OnCreate() override;
		void OnUpdate() override;
	};
}