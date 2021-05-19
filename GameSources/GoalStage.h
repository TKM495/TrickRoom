/*!
@file GoalStage.h
@brief �S�[���X�e�[�W
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class GoalStage :public Stage {
		int m_stageNum;

		void CreateViewLight();
	public:
		GoalStage(int stageNum = 1)
			:Stage(), m_stageNum(stageNum)
		{}

		void OnCreate()override;
	};
}
//end basecross