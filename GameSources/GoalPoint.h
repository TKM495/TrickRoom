#pragma once
#include "stdafx.h"
#include "StageObject.h"

namespace basecross {
	class GoalPoint :public StageObject {
	public:
		GoalPoint(const shared_ptr<Stage>& stage,
			const ObjectParam& param)
			:StageObject(stage)
		{
			m_position = param.position;
			m_rotation = param.rotation;
		}

		void OnCreate()override;
	};
}
//end basecross