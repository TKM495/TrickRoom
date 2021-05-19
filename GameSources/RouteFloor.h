/*!
@file RouteFloor.h
@brief
*/

#pragma once
#include "stdafx.h"
#include "RouteMove.h"
#include "TimeCounter.h"

namespace basecross {
	class RouteFloor : public StageObject {
		float m_speed;
		Vec3 m_before;
		Vec3 m_now;
		Vec3 m_move;
		Vec3 m_respawnPos;
		bool m_bRespawn;
		RouteMove::MoveDir m_moveDir;
		TimeCounter m_timer;
	public:
		RouteFloor(const shared_ptr<Stage>& StagePtr,
			const wstring& line);
		virtual ~RouteFloor();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		Vec3 GetMove() {
			return m_move;
		}
	};
}
//end basecross
