/*!
@file Plane.cpp
@brief 板オブジェクト実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Plane::Plane(shared_ptr<Stage>& stage,
		const wstring& line)
		:StageObject(stage)
	{
		//トークン（カラム）の配列
		vector<wstring> tokens;
		Util::WStrToTokenVector(tokens, line, L',');
		//各トークン（カラム）をスケール、回転、位置に読み込む
		m_position = Vec3(
			(float)_wtof(tokens[1].c_str()),
			(float)_wtof(tokens[2].c_str()),
			(float)_wtof(tokens[3].c_str())
		);
		m_scale = Vec3(
			(float)_wtof(tokens[4].c_str()),
			(float)_wtof(tokens[5].c_str()),
			(float)_wtof(tokens[6].c_str())
		);
		m_rotation = Vec3(
			XMConvertToRadians((float)_wtof(tokens[7].c_str())),
			XMConvertToRadians((float)_wtof(tokens[8].c_str())),
			XMConvertToRadians((float)_wtof(tokens[9].c_str()))
		);
	}


	void Plane::OnCreate() {
		//色のデータ(R,G,B,A)
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		//頂点のデータ (番号は左上から右下まで)
		vector<VertexPositionColorTexture> vertices = {
			{Vec3(-0.5f, +0.5f, 0.0f),color,Vec2(0.0f,0.0f)}, //0
			{Vec3(+0.5f, +0.5f, 0.0f),color,Vec2(1.0f,0.0f)}, //1
			{Vec3(-0.5f, -0.5f, 0.0f),color,Vec2(0.0f,1.0f)}, //2
			{Vec3(+0.5f, -0.5f, 0.0f),color,Vec2(1.0f,1.0f)}  //3
		};
		//頂点インデックス(頂点をつなげる順番)
		std::vector<uint16_t> indices = {
			0, 1, 2, //上の三角形
			2, 1, 3  //下の三角形
		};
		auto collComp = AddComponent<CollisionRect>();
		collComp->SetFixed(true);

		auto drawComp = AddComponent<BcPNTStaticDraw>();
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
		transComp->SetRotation(m_rotation);
	}
}
//end basecross
