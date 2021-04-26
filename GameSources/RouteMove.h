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
		//�Փˎ��ɋȂ������
		enum class TurnDir {
			Right,
			Left
		};
		//�ړ�����(�O���ݒ�p)
		enum class MoveDir {
			Up,
			Left,
			Down,
			Right
		};
	private:
		//�ړ����x
		float m_Speed;
		//�ړ��������`����z��
		Vec3 m_moveDir[4];
		//�����݂̈ړ�����
		int m_moveIndex;
		//�Փˎ��ɂǂ̕����Ɉړ����邩
		TurnDir m_turnDir;
		//�����蔻��̃I�u�W�F�N�g�|�C���^
		shared_ptr<AdvCollision> m_collision;
	public:
		RouteMove(const shared_ptr<GameObject>& obj)
			: Behavior(obj), m_Speed(3), m_turnDir(TurnDir::Left),
			m_moveIndex(0)
		{
			//�z��Ɉړ���������
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

		void SetMoveDir(MoveDir move) {
			m_moveIndex = (int)move;
		}
	};
}