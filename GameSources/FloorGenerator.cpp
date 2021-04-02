/*!
@file FloorGenerator.cpp
@brief 床生成実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	FloorGenerator::FloorGenerator(const shared_ptr<Stage>& stage,
		const wstring& line)
		:GameObject(stage)
	{
		//トークン（カラム）の配列
		vector<wstring> tokens;
		Util::WStrToTokenVector(tokens, line, L',');
		m_origin = Vec3(
			(float)_wtof(tokens[1].c_str()),
			(float)_wtof(tokens[2].c_str()),
			(float)_wtof(tokens[3].c_str())
		);
		m_width = (int)_wtof(tokens[4].c_str());
		m_height = (int)_wtof(tokens[5].c_str());
	}

	void FloorGenerator::OnCreate() {
		auto stage = GetStage();
		for (int i = 0; i < m_height; i++) {
			for (int j = 0; j < m_width; j++) {
				Vec3 offset(j, 0.0f, i);

				auto plane = stage->AddGameObject<Plane>(L"");
				auto transComp = plane->GetComponent<Transform>();
				transComp->SetPosition(m_origin + offset);
				transComp->SetRotation(Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f));
			}
		}
	}

}
//end basecross
