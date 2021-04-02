/*!
@file AdvCollision.h
@brief 高度な当たり判定
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
		//基準となる位置
		shared_ptr<GameObject> m_parent;
		//オフセット
		Vec3 m_offset;
		//スケール
		Vec3 m_scale;
		//回転
		Vec3 m_rotation;
		//コリジョンの形
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
