/*!
@file StageObject.cpp
@brief ステージに配置するオブジェクトの基底クラスの実体
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
