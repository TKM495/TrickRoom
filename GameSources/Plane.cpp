/*!
@file Plane.cpp
@brief 板オブジェクト実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Plane::OnCreate() {
		//色のデータ(R,G,B,A)
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		//頂点のデータ (番号は左上から右下まで)
		vector<VertexPositionColorTexture> vertices = {
			{Vec3(-0.5f, 0.0f,+0.5f),color,Vec2(0.0f,0.0f)}, //0
			{Vec3(+0.5f, 0.0f,+0.5f),color,Vec2(1.0f,0.0f)}, //1
			{Vec3(-0.5f, 0.0f,-0.5f),color,Vec2(0.0f,1.0f)}, //2
			{Vec3(+0.5f, 0.0f,-0.5f),color,Vec2(1.0f,1.0f)}  //3
		};
		//頂点インデックス(頂点をつなげる順番)
		std::vector<uint16_t> indices = {
			0, 1, 2, //上の三角形
			2, 1, 3  //下の三角形
		};

		auto collComp = AddComponent<CollisionObb>();
		collComp->SetFixed(true);

		auto drawComp = AddComponent<PCTStaticDraw>();
		//頂点データと頂点インデックスをもとにメッシュ(ポリゴン)を生成する
		drawComp->CreateOriginalMesh(vertices, indices);
		//自作したメッシュを使用する
		drawComp->SetOriginalMeshUse(true);
		//drawComp->SetTextureResource(L"SpikesArt");

		//drawComp->SetSamplerState(SamplerState::AnisotropicWrap); //テクスチャの繰り返し設定(Wrap)
		//drawComp->SetDepthStencilState(DepthStencilState::Read);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		transComp->SetScale(m_scale);
	}
}
//end basecross
