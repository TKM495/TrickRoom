#pragma once
#include "stdafx.h"

namespace basecross {
	class Goal : public GameObject
	{
	public :
		Goal(const std::shared_ptr<Stage>& stage)
			: GameObject(stage)
		{
		}
		
		void OnCreate() override;
	};
}
