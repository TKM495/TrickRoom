/*!
@file illusionModel.cpp
@brief 錯視モデルの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void illusionModel::OnCreate() {
		wstring texName = L"";
		switch (m_type)
		{
		case Type::Triangle:
			texName = L"TriangleModel";
			break;
		case Type::Stairs:
			texName = L"StairsModel";
			break;
		case Type::Cube:
			texName = L"CubeModel";
			break;
		case Type::Arch:
			texName = L"ArchModel";
			break;
		case Type::Rectangle:
			texName = L"RectangleModel";
			break;
		default:
			//エラー
			break;
		}

		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(texName);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		transComp->SetScale(m_scale);
		transComp->SetRotation(Utility::ConvertDegVecToRadVec(m_rotation));
	}
}
//end basecross