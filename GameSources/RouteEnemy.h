/*!
@file RouteEnemy.h
@brief
*/

#pragma once
#include "stdafx.h"
#include "AdvCollision.h"

namespace basecross {
	class RouteEnemy :public StageObject, public TrickArtBase {
		float m_speed;
		Vec3 m_before;
		Vec3 m_now;
		float m_delta;
	public:
		RouteEnemy(const shared_ptr<Stage>& stage,
			const wstring& line);

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void OnCollisionEnter(shared_ptr<GameObject>& other) override;
	};
}
//end basecross
