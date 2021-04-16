/*!
@file PictureFrame.h
@brief StageSelect�Ŏg�����
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PictureFrame :public GameObject {
		//���݂̃X�e�[�W(0�`)
		int m_nowStage;
	public:
		PictureFrame(const shared_ptr<Stage>& stage,
			int num)
			:GameObject(stage),
			m_nowStage(num)
		{}

		void OnCreate()override;
	};
}
//end basecross
