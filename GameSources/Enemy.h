/*!
@file Enemy.h
@brief
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Enemy :public StageObject ,public TrickArtBase{
		wstring m_behavior;
		float m_cycle;
		float m_speed;
		float m_offset;
	public:
		Enemy(const shared_ptr<Stage>& stage,
			const wstring& line);

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void OnCollisionEnter(shared_ptr<GameObject>& other) override;
	};
}
//end basecross
