/*!
@file StageObject.h
@brief �X�e�[�W�ɔz�u����I�u�W�F�N�g�̐e�N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class StageObject :public GameObject {
	protected:
		Vec3 m_position;
		Vec3 m_scale;
	public:
		StageObject(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}
	};

}
//end basecross
