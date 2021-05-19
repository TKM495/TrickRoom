/*!
@file VirtualFloor.cpp
@brief 仮想床(テクスチャが貼れないオブジェクトに貼る用)クラス
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	VirtualFloor::VirtualFloor(const shared_ptr<Stage>& stage,
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
		m_bProjActive = tokens[10] == L"TRUE" ? true : false;
	}

	void VirtualFloor::OnCreate() {
		vector<Vec2> uv = {
			Vec2(0.0f,0.0f),
			Vec2(m_scale.x / 1.0f,0.0f),
			Vec2(0.0f,m_scale.z / 1.0f),
			Vec2(m_scale.x / 1.0f,m_scale.z / 1.0f)
		};

		//色のデータ(R,G,B,A)
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		Vec3 up(-1.0f, 0.0f, 0.0f);
		//頂点のデータ (番号は左上から右下まで)
		//ZではなくYを使っているのは当たり判定の関係上
		vector<VertexPositionNormalTexture> vertices = {
			{Vec3(-0.5f, 0.0f, +0.5f),up,uv[0]}, //0
			{Vec3(+0.5f, 0.0f, +0.5f),up,uv[1]}, //1
			{Vec3(-0.5f, 0.0f, -0.5f),up,uv[2]}, //2
			{Vec3(+0.5f, 0.0f, -0.5f),up,uv[3]}  //3
		};
		//頂点インデックス(頂点をつなげる順番)
		std::vector<uint16_t> indices = {
			0, 1, 2, //上の三角形
			2, 1, 3  //下の三角形
		};

		shared_ptr<SmBaseDraw> ptrDraw;
		if (m_bProjActive) {
			ptrDraw = AddComponent<PNTStaticDraw2>();
		}
		else {
			ptrDraw = AddComponent<PNTStaticDraw>();
		}
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->CreateOriginalMesh(vertices, indices);
		ptrDraw->SetOriginalMeshUse(true);
		ptrDraw->SetTextureResource(L"Floor");

		ptrDraw->SetSamplerState(SamplerState::AnisotropicWrap);
		ptrDraw->SetDepthStencilState(DepthStencilState::Read);

		StageObject::ObjectSetUp();
	}
}
//end basecross