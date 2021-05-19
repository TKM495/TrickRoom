#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void FloorModel::OnCreate() {
		auto shadow = AddComponent<Shadowmap>();
		shadow->SetMeshResource(L"DEFAULT_CUBE");

		auto draw = AddComponent<PNTStaticDraw>();
		draw->SetMeshResource(L"DEFAULT_CUBE");
		draw->SetOwnShadowActive(true);

		auto col = AddComponent<CollisionObb>();
		//col->SetFixed(true);
		col->AddExcludeCollisionGameObject(m_floor);

		auto myTrans = GetComponent<Transform>();
		auto floorTrans = m_floor->GetComponent<Transform>();
		myTrans->SetScale(floorTrans->GetScale());
		myTrans->SetPosition(floorTrans->GetPosition());
		//myTrans->SetParent(m_floor);
	}

	void FloorModel::OnUpdate() {
		auto myTrans = GetComponent<Transform>();
		auto floorTrans = m_floor->GetComponent<Transform>();
		myTrans->SetPosition(floorTrans->GetPosition());
	}

	void FloorModel::OnCollisionEnter(shared_ptr<GameObject>& other) {
		auto state = dynamic_pointer_cast<GameStage>(GetStage())->GetState();
		auto camera = dynamic_pointer_cast<MainCamera>(OnGetDrawCamera());
		switch (state)
		{
		default:
			if (other->FindTag(L"Player") &&
				!camera->GetbLeapFlg()) {
				auto playerTrans = other->GetComponent<Transform>();
				auto pos = playerTrans->GetPosition();
				pos += -m_floor->GetMove();
				playerTrans->SetPosition(pos);
			}
			break;
		case basecross::GameStage::GameState::PAUSE:
			break;
		}
	}

	void FloorModel::OnCollisionExcute(shared_ptr<GameObject>& other) {
		auto state = dynamic_pointer_cast<GameStage>(GetStage())->GetState();
		auto camera = dynamic_pointer_cast<MainCamera>(OnGetDrawCamera());
		switch (state)
		{
		default:
			if (other->FindTag(L"Player") &&
				!camera->GetbLeapFlg()) {
				auto playerTrans = other->GetComponent<Transform>();
				auto pos = playerTrans->GetPosition();
				pos += -m_floor->GetMove();
				playerTrans->SetPosition(pos);
			}
			break;
		case basecross::GameStage::GameState::PAUSE:
			break;
		}
	}

}