/*!
@file ArtCollision.cpp
@brief çÇìxÇ»ìñÇΩÇËîªíËé¿ëÃ
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
				L"å`èÛÇÃéwíËÇ™Ç†ÇËÇ‹ÇπÇÒ",
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
		auto parentPos = parentTrans->GetPosition();

		auto scale = Vec3(
			m_scale.x * parentScale.x,
			m_scale.y * parentScale.y,
			m_scale.z * parentScale.z
		);
		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(parentPos + m_offset);
		transComp->SetScale(scale);
		transComp->SetRotation(m_rotation);
	}

	void AdvCollision::OnUpdate() {
		auto myTrans = GetComponent<Transform>();
		auto parentTrans = m_parent->GetComponent<Transform>();
		myTrans->SetPosition(parentTrans->GetPosition()+ m_offset);
	}

	void AdvCollision::SetActive(bool flg) {
		GetComponent<Collision>()->SetUpdateActive(flg);
	}

	void AdvCollision::SetAfterCollision(AfterCollision col) {
		GetComponent<Collision>()->SetAfterCollision(col);
	}

	void AdvCollision::OnCollisionEnter(shared_ptr<GameObject>& other) {
		m_bHit = true;
		m_hitObj = other;
	}
	void AdvCollision::OnCollisionExit(shared_ptr<GameObject>& other) {
		m_bHit = false;
		m_hitObj = nullptr;
	}

}
//end basecross
