/*!
@file SinCurve.h
@brief サインカーブ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SinCurve :public Behavior {
		Vec3 m_Position;
		float m_offset;
		float m_TotalTime;
	public:
		SinCurve(const shared_ptr<GameObject>& obj)
			:Behavior(obj), m_TotalTime(0.0f),
			m_offset(0.0f)
		{}

		virtual void OnCreate()override;
		void SetOffset(float offset) {
			m_offset = offset;
		}
		void Excute(float cycle, float speed);
	};

}
//end basecross
