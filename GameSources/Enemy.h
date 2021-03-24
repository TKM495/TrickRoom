/*!
@file Enemy.h
@brief �G
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Enemy :public StageObject {
		float m_TotalTime;
	public:
		Enemy(const shared_ptr<Stage>& stage,
			const wstring& line);

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};
}
//end basecross
