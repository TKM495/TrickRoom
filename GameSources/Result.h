/*!
@file Result.h
@brief Œ‹‰Ê
*/

#pragma once
#include "stdafx.h"
#include "StringSprite2.h"
#include "GameStage.h"
#include "SpriteManager.h"

namespace basecross {
	class Result :public GameObject {
		float m_strSize;
		float m_numSize;
	public:
		Result(const shared_ptr<Stage>& stage)
			:GameObject(stage),
			m_strSize(0.8f),
			m_numSize(0.5f)
		{}

		virtual void OnCreate()override;
	};

}
//end basecross
