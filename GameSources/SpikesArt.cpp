/*!
@file SpikesArt.cpp
@brief トリックアートの棘クラスの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void SpikesArt::OnCreate() {
		m_position = Vec3(0.0f,-0.49f,0.0f);
		m_scale = Vec3(1.0f);

		auto halfSize = m_artSize / 2.0f;

		//色のデータ(R,G,B,A)
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		//頂点のデータ (番号は左上から右下まで)
		vector<VertexPositionColorTexture> vertices = {
			{Vec3(-halfSize, 0.0f,+halfSize),color,Vec2(0.0f,0.4f)}, //0
			{Vec3(+halfSize, 0.0f,+halfSize),color,Vec2(1.0f,0.4f)}, //1
			{Vec3(-halfSize, 0.0f,-halfSize),color,Vec2(0.0f,1.0f)}, //2
			{Vec3(+halfSize, 0.0f,-halfSize),color,Vec2(1.0f,1.0f)}  //3
		};
		//頂点インデックス(頂点をつなげる順番)
		std::vector<uint16_t> indices = {
			0, 1, 2, //上の三角形
			2, 1, 3  //下の三角形
		};

		auto drawComp = AddComponent<PCTStaticDraw>();
		//頂点データと頂点インデックスをもとにメッシュ(ポリゴン)を生成する
		drawComp->CreateOriginalMesh(vertices, indices);
		//自作したメッシュを使用する
		drawComp->SetOriginalMeshUse(true);
		drawComp->SetTextureResource(L"SpikesArt");

		drawComp->SetSamplerState(SamplerState::AnisotropicWrap); //テクスチャの繰り返し設定(Wrap)
		drawComp->SetDepthStencilState(DepthStencilState::Read);

		SetAlphaActive(true); //透明をサポートする&両面描画になる



			auto obbComp = AddComponent<CollisionObb>();
			obbComp->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		transComp->SetScale(m_scale);
		transComp->SetRotation(0.0f, XMConvertToRadians(-45.0f),0.0f);

		//当たり判定の切り替えでダメージの判定を行うため
		//常にこのタグを持つ
		AddTag(L"damege");
	}
}
//end basecross