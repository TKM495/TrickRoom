/*!
@file AdvCollision.h
@brief ���x�ȓ����蔻��
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class AdvCollision :public GameObject {
	public:
		enum class Shape {
			Obb,
			Sphere,
			Capsule,
			Rect
		};
	private:
		//��ƂȂ�ʒu
		shared_ptr<GameObject> m_parent;
		//�I�t�Z�b�g
		Vec3 m_offset;
		//�X�P�[��
		Vec3 m_scale;
		//��]
		Vec3 m_rotation;
		//�R���W�����̌`
		AdvCollision::Shape m_collShape;
		//�����ɓ����������ǂ���
		bool m_bHit;
		//���������I�u�W�F�N�g�̏��
		shared_ptr<GameObject> m_hitObj;
	public:
		AdvCollision(const shared_ptr<Stage>& stage,
			const shared_ptr<GameObject>& parent,
			const Vec3& offset,
			const Vec3& scale,
			const Vec3& rotation,
			Shape shape)
			:GameObject(stage),
			m_parent(parent),
			m_offset(offset),
			m_scale(scale),
			m_rotation(rotation),
			m_collShape(shape),
			m_bHit(false)
		{}
		AdvCollision(const shared_ptr<Stage>& stage,
			const shared_ptr<GameObject>& parent,
			Shape shape)
			:GameObject(stage),
			m_parent(parent),
			m_offset(Vec3(0.0f)),
			m_scale(Vec3(1.0f)),
			m_rotation(Vec3(0.0f)),
			m_collShape(shape),
			m_bHit(false)
		{}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		template<typename T>
		void bHit() {
			if (m_bHit) {
				auto obj = dynamic_pointer_cast<T>(m_parent);
				obj->OnCollisionEnter(m_hitObj);
			}
		}
		bool bHit() {
			return m_bHit;
		}
		void SetActive(bool flg);
		void SetAfterCollision(AfterCollision col);
		void OnCollisionEnter(shared_ptr<GameObject>& other) override;
		void OnCollisionExit(shared_ptr<GameObject>& other) override;
	};

}
//end basecross
