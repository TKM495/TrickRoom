/*!
@file UI_Player.h
@brief ìÆÇ≠ÉvÉåÉCÉÑÅ[ÇÃUIÇ»Ç«
*/

#pragma once
#include "stdafx.h"

namespace basecross
{
	class UI_Player : public GameObject
	{
		float m_startPosX;
		float m_goalPosX;
		float m_startObjPosX;
		float m_goalObjPosX;
		float m_startToGoalDir;
		bool bActive;
	public:
		UI_Player(const std::shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_startPosX(0.0f),
			m_goalPosX(0.0f),
			bActive(false)
		{}

		void OnCreate() override;
		void OnUpdate() override;

		void FadeIn();
	};
}