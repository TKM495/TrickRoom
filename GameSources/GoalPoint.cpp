#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void GoalPoint::OnCreate() {
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		auto halfWidth = 2.0f / 2.0f;
		auto halfHeight = 1.5f / 2.0f;
		vector<VertexPositionColorTexture> vertices = {
			{Vec3(-halfWidth, 0.0f, +1.5f),color,Vec2(0.0f,0.0f)}, //0
			{Vec3(+halfWidth, 0.0f, +1.5f),color,Vec2(1.0f,0.0f)}, //1
			{Vec3(-halfWidth, 0.0f, -0.0f),color,Vec2(0.0f,1.0f)}, //2
			{Vec3(+halfWidth, 0.0f, -0.0f),color,Vec2(1.0f,1.0f)}  //3
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
		drawComp->SetTextureResource(L"GoalPoint");

		drawComp->SetSamplerState(SamplerState::AnisotropicWrap);
		drawComp->SetDepthStencilState(DepthStencilState::Read);
		SetAlphaActive(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		transComp->SetScale(Vec3(1.0f));
		transComp->SetRotation(m_rotation);
	}
}
//end basecross