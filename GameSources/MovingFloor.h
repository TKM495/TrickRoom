/*!
@file MovingFloor.h
@brief
*/

#pragma once
#include "stdafx.h"
#include "TimeCounter.h"
#include "StageObject.h"

namespace basecross {
	class MovingFloor : public StageObject {
		wstring m_behavior;
		Vec3 m_startPos;
		Vec3 m_endPos;
		float m_speed;
		float m_offset;
		Vec3 m_before;
		Vec3 m_now;
		Vec3 m_move;
		TimeCounter m_timer;
	public:
		MovingFloor(const shared_ptr<Stage>& stage,
			const wstring& line);
		void OnCreate()override;
		void OnUpdate()override;

		Vec3 GetMove() {
			return m_move;
		}
	};
}
//end basecross