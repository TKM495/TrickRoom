#pragma once
#include "stdafx.h"
#include "StageObject.h"

namespace basecross {
	class Goal :public StageObject {
	public:
		Goal(const shared_ptr<Stage>& stage,
			const wstring& line);

		void OnCreate()override;
	};
}
//end basecross