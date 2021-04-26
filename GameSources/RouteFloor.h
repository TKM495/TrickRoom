/*!
@file RouteFloor.h
@brief
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class RouteFloor : public StageObject, public TrickArtBase {
		float m_speed;
		Vec3 m_before;
		Vec3 m_now;
		float m_delta;
	public:
		RouteFloor(const shared_ptr<Stage>& StagePtr,
			const wstring& line);
		virtual ~RouteFloor();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}
//end basecross
