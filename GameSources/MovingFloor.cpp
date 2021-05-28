/*!
@file MovingFloor.cpp
@brief
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MovingFloor::MovingFloor(const shared_ptr<Stage>& StagePtr,
		const wstring& line)
		:StageObject(StagePtr)
	{
		vector<wstring> tokens;
		Util::WStrToTokenVector(tokens, line, L',');
		m_position = Vec3(
			(float)_wtof(tokens[1].c_str()),
			(float)_wtof(tokens[2].c_str()),
			(float)_wtof(tokens[3].c_str())
		);
		m_scale = Vec3(
			(float)_wtof(tokens[4].c_str()),
			(float)_wtof(tokens[5].c_str()),
			(float)_wtof(tokens[6].c_str())
		);
		m_rotation = Vec3(
			XMConvertToRadians((float)_wtof(tokens[7].c_str())),
			XMConvertToRadians((float)_wtof(tokens[8].c_str())),
			XMConvertToRadians((float)_wtof(tokens[9].c_str()))
		);

		m_startPos = Vec3(
			(float)_wtof(tokens[10].c_str()),
			(float)_wtof(tokens[11].c_str()),
			(float)_wtof(tokens[12].c_str())
		);
		m_endPos = Vec3(
			(float)_wtof(tokens[13].c_str()),
			(float)_wtof(tokens[14].c_str()),
			(float)_wtof(tokens[15].c_str())
		);
		m_speed = (float)_wtof(tokens[16].c_str());
		m_offset = (float)_wtof(tokens[17].c_str());
	}

	void MovingFloor::OnCreate() {
		StageObject::ObjectSetUp();

		GetStage()->AddGameObject<FloorModel>(GetThis<MovingFloor>());

		auto col = AddComponent<CollisionObb>();
		col->AddExcludeCollisionTag(L"Player");
		auto scene = App::GetApp()->GetScene<Scene>();
		if (scene->GetDebugState() == DebugState::Debug) {
			col->SetDrawActive(true);
		}

		auto beh = GetBehavior<LinerMove>();
		beh->SetMovePositions(m_startPos, m_endPos);
		beh->SetSpeed(m_speed);
		beh->SetOffset(m_offset);
	}

	void MovingFloor::OnUpdate() {
		auto state = dynamic_pointer_cast<GameStage>(GetStage())->GetState();
		auto camera = dynamic_pointer_cast<MainCamera>(GetStage()->GetView()->GetTargetCamera());
		auto trans = GetComponent<Transform>();

		if (camera->GetbLeapFlg()) {
			return;
		}
		m_before = m_now;
		m_now = trans->GetPosition();
		switch (state)
		{
		default:
			m_move = m_before - m_now;
			GetBehavior<LinerMove>()->Excute();
			break;
		case basecross::GameStage::GameState::PAUSE:
			break;
		}
	}
}
//end basecross