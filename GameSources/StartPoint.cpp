#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void StartPoint::OnCreate() {
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		auto halfSize = m_size / 2.0f;
		vector<VertexPositionColorTexture> vertices = {
			{Vec3(-halfSize, 0.0f, +halfSize),color,Vec2(0.0f,0.0f)}, //0
			{Vec3(+halfSize, 0.0f, +halfSize),color,Vec2(1.0f,0.0f)}, //1
			{Vec3(-halfSize, 0.0f, -halfSize),color,Vec2(0.0f,1.0f)}, //2
			{Vec3(+halfSize, 0.0f, -halfSize),color,Vec2(1.0f,1.0f)}  //3
		};
		//頂点インデックス(頂点をつなげる順番)
		std::vector<uint16_t> indices = {
			0, 1, 2, //上の三角形
			2, 1, 3  //下の三角形
		};

		auto drawComp = AddComponent<PCTStaticDraw>();
		drawComp->SetOwnShadowActive(true);
		drawComp->CreateOriginalMesh(vertices, indices);
		drawComp->SetOriginalMeshUse(true);
		drawComp->SetTextureResource(L"StartPoint");

		drawComp->SetSamplerState(SamplerState::AnisotropicWrap);
		drawComp->SetDepthStencilState(DepthStencilState::Read);
		SetAlphaActive(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		transComp->SetRotation(Utility::ConvertDegVecToRadVec(Vec3(0.0f, -90.0f, 0.0f)));

	}
}
//end basecross