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
		//移動時に制限をかける軸
		enum class LimitAxis {
			X,
			Z
		};
		//衝突時に曲がる方向
		enum class TurnDir {
			Right,
			Left
		};
		//初期の移動方向(外部設定用)
		enum class MoveDir {
			Up,
			Left,
			Down,
			Right
		};
	private:
		//初期位置
		Vec3 m_defPos;
		//移動速度
		float m_Speed;
		//衝突フラグ
		bool m_bHit;
		//移動方向を定義する配列
		Vec3 m_moveDir[4];
		//移動方向の制限の定義
		LimitAxis m_limitAxis[4];
		//今現在の移動方向
		int m_moveIndex;
		//衝突時にどの方向に移動するか
		TurnDir m_turnDir;
		//当たり判定のオブジェクトポインタ
		shared_ptr<AdvCollision> m_collision;
	public:
		RouteMove(const shared_ptr<GameObject>& obj)
			: Behavior(obj), m_Speed(3), m_turnDir(TurnDir::Left),
			m_moveIndex(0), m_bHit(false)
		{
			//配列に移動方向を代入
			m_moveDir[0] = Vec3(0.0f, 0.0f, 1.0f);
			m_moveDir[1] = Vec3(-1.0f, 0.0f, 0.0f);
			m_moveDir[2] = Vec3(0.0f, 0.0f, -1.0f);
			m_moveDir[3] = Vec3(1.0f, 0.0f, 0.0f);
			//配列に制限する軸を定義
			m_limitAxis[0] = LimitAxis::X;
			m_limitAxis[1] = LimitAxis::Z;
			m_limitAxis[2] = LimitAxis::X;
			m_limitAxis[3] = LimitAxis::Z;
		}

		void OnCreate()override;
		void Excute();

		void Hit();

		void SetSpeed(float speed) {
			m_Speed = speed;
		}

		void SetTurnDir(TurnDir turn) {
			m_turnDir = turn;
		}

		void SetMoveDir(MoveDir move) {
			m_moveIndex = (int)move;
		}
	};
}