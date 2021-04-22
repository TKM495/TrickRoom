/*!
@file RouteMove.h
@brief ƒ‹[ƒg‚É‰ˆ‚Á‚½“®‚«‚È‚Ç
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class RouteMove : public Behavior {
		float m_Speed;
		bool bHitFlg;
		bool bNotHitFlg;
		bool bjudgment;
		float m_counter;
		float m_Time;
		bool bwalljudg;

	public:
		RouteMove(const shared_ptr<GameObject>& obj)
			: Behavior(obj), m_Speed(3), bHitFlg(false),
			bNotHitFlg(false), m_counter(0), bjudgment(true),
			m_Time(5), bwalljudg(false)
		{

		}

		//void OnCreate() override;
		void Excute();

		void Hit(bool flg);

		void SetSpeed(float speed) {
			m_Speed = speed;
		}
	};
}