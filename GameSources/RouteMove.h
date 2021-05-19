/*!
@file RouteMove.h
@brief ���[�g�ɉ����������Ȃ�
*/

#pragma once
#include "stdafx.h"
#include "AdvCollision.h"

namespace basecross {
	class RouteMove : public Behavior {
	public:
		//�ړ����ɐ����������鎲
		enum class LimitAxis {
			X,
			Z
		};
		//�Փˎ��ɋȂ������
		enum class TurnDir {
			Right,
			Left
		};
		//�����̈ړ�����(�O���ݒ�p)
		enum class MoveDir {
			Up,
			Left,
			Down,
			Right
		};
	private:
		//�����ʒu
		Vec3 m_defPos;
		//�ړ����x
		float m_Speed;
		//�Փ˃t���O
		bool m_bHit;
		//�ړ��������`����z��
		Vec3 m_moveDir[4];
		//�ړ������̐����̒�`
		LimitAxis m_limitAxis[4];
		//�����݂̈ړ�����
		int m_moveIndex;
		//�Փˎ��ɂǂ̕����Ɉړ����邩
		TurnDir m_turnDir;
		//�����蔻��̃I�u�W�F�N�g�|�C���^
		shared_ptr<AdvCollision> m_collision;
	public:
		RouteMove(const shared_ptr<GameObject>& obj)
			: Behavior(obj), m_Speed(3), m_turnDir(TurnDir::Left),
			m_moveIndex(0), m_bHit(false)
		{
			//�z��Ɉړ���������
			m_moveDir[0] = Vec3(0.0f, 0.0f, 1.0f);
			m_moveDir[1] = Vec3(-1.0f, 0.0f, 0.0f);
			m_moveDir[2] = Vec3(0.0f, 0.0f, -1.0f);
			m_moveDir[3] = Vec3(1.0f, 0.0f, 0.0f);
			//�z��ɐ������鎲���`
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