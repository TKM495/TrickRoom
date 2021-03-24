/*!
@file ArtCollision.cpp
@brief 高度な当たり判定実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void AdvCollision::OnCreate() {
		shared_ptr<Collision> collComp;
		switch (m_collShape)
		{
		case basecross::AdvCollision::Shape::Obb:
			collComp = AddComponent<CollisionObb>();
			break;
		case basecross::AdvCollision::Shape::Sphere:
			collComp = AddComponent<CollisionSphere>();
			break;
		case basecross::AdvCollision::Shape::Capsule:
			collComp = AddComponent<CollisionCapsule>();
			break;
		case basecross::AdvCollision::Shape::Rect:
			collComp = AddComponent<CollisionRect>();
			break;
		default:
			throw BaseException(
				L"形状の指定がありません",
				L"m_collShape is null ",
				L"AdvCollision::OnCreate()"
			);
			break;
		}
		collComp->SetFixed(true);
		collComp->SetDrawActive(true);

		auto parentTrans = m_parent->GetComponent<Transform>();
		auto parentScale = parentTrans->GetScale();

		auto scale = Vec3(
			m_scale.x * parentScale.x,
			m_scale.y * parentScale.y,
			m_scale.z * parentScale.z
		);

		auto transComp = GetComponent<Transform>();
		transComp->SetParent(m_parent);
		transComp->SetPosition(m_offset);
		transComp->SetScale(scale);
		transComp->SetRotation(m_rotation);
	}

	void AdvCollision::SetActive(bool flg) {
		GetComponent<Collision>()->SetUpdateActive(flg);
	}
}
//end basecross
