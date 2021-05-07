/*!
@file StageObject.cpp
@brief �X�e�[�W�ɔz�u����I�u�W�F�N�g�̊��N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void StageObject::ObjectSetUp() {
		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		transComp->SetScale(m_scale);
		transComp->SetRotation(m_rotation);
		AddTag(L"StageObject");
	}
}
//end basecross
