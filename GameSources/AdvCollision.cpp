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

		auto scene = App::GetApp()->GetScene<Scene>();
		if (scene->GetDebugState() == DebugState::Debug) {
			collComp->SetDrawActive(true);
		}

		auto parentTrans = m_parent->GetComponent<Transform>();
		auto parentScale = parentTrans->GetScale();

		auto scale = Vec3(
			m_scale.x * parentScale.x,
			m_scale.y * parentScale.y,
			m_scale.z * parentScale.z
		);
		auto pos = Vec3(
			m_offset.x * parentScale.x,
			m_offset.y * parentScale.y,
			m_offset.z * parentScale.z
		);
		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(pos);
		transComp->SetScale(scale);
		transComp->SetRotation(m_rotation);
	}

	void AdvCollision::OnUpdate() {
		auto myTrans = GetComponent<Transform>();
		auto parentTrans = m_parent->GetComponent<Transform>();
		myTrans->SetPosition(parentTrans->GetPosition());
	}

	void AdvCollision::SetActive(bool flg) {
		GetComponent<Collision>()->SetUpdateActive(flg);
	}

	//void AdvCollision::OnCollisionEnter(shared_ptr<GameObject>& other) {
	//	m_parent->OnCollisionEnter(other);
	//}
}
//end basecross
