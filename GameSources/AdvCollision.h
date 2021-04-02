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
			m_collShape(shape)
		{}
		virtual void OnCreate()override;
		void SetActive(bool flg);
	};

}
//end basecross
