/*!
@file TitleModel.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TitleModel::OnCreate() {
		auto drawComp = AddComponent<BcPNTStaticModelDraw>();
		drawComp->SetMeshResource(L"Title");

		auto shadow = AddComponent<Shadowmap>();
		shadow->SetMeshResource(L"Title");

		auto trans = GetComponent<Transform>();
		trans->SetPosition(-6.0f, 0.0f, 0.0f);
	}

}
//end basecross
