#pragma once
#include "stdafx.h"
#include "StageObject.h"

namespace basecross {
	class GoalModel : public GameObject
	{
		ObjectParam m_param;
		bool m_bOpen;
		bool m_bOnce;
	public :
		GoalModel(const std::shared_ptr<Stage>& stage,
			ObjectParam param);

		void OnCreate() override;
		void OnUpdate() override;
	};
}
