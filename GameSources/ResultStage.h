/*!
@file ResultStage.h
@brief ���ʉ��
*/

#pragma once
#include "stdafx.h"
#include "Result.h"

namespace basecross {
	class ResultStage : public Stage {
	public:
		ResultStage()
			:Stage()
		{}

		// �r���[�̍쐬
		void CreateViewLight();

		void OnCreate() override;
		void OnUpdate() override;

		//void PushB();
	};

}
//end basecross
