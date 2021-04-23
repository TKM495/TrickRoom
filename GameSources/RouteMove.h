/*!
@file RouteMove.h
@brief ルートに沿った動きなど
*/

#pragma once
#include "stdafx.h"
#include "AdvCollision.h"

namespace basecross {
	class RouteMove : public Behavior {
	public:
		//衝突時に曲がる方向
		enum class TurnDir {
			Right,
			Left
		};
	private:
		//移動速度
		float m_Speed;
		//移動方向を定義する配列
		Vec3 m_moveDir[4];
		//今現在の移動方向
		int m_moveIndex;
		//衝突時にどの方向に移動するか
		TurnDir m_turnDir;
		//当たり判定のオブジェクトポインタ
		shared_ptr<AdvCollision> m_collision;
	public:
		RouteMove(const shared_ptr<GameObject>& obj)
			: Behavior(obj), m_Speed(3), m_turnDir(TurnDir::Right),
			m_moveIndex(0)
		{
			//配列に移動方向を代入
			m_moveDir[0] = Vec3(0.0f, 0.0f, 1.0f);
			m_moveDir[1] = Vec3(-1.0f, 0.0f, 0.0f);
			m_moveDir[2] = Vec3(0.0f, 0.0f, -1.0f);
			m_moveDir[3] = Vec3(1.0f, 0.0f, 0.0f);
		}

		void Excute();

		void Hit();

		void SetSpeed(float speed) {
			m_Speed = speed;
		}

		void SetTurnDir(TurnDir turn) {
			m_turnDir = turn;
		}
	};
}