/*!
@file Picture.cpp
@brief 雰囲気を出すための絵実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Picture::Picture(const shared_ptr<Stage>& stage,
		const wstring& line)
		:StageObject(stage)
	{
		vector<wstring> tokens;
		Util::WStrToTokenVector(tokens, line, L',');
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
		m_texName = tokens[10];
	}

	void Picture::OnCreate() {
		//CSVLoadを取得しデータをもらう
		auto csvLoad = dynamic_pointer_cast<CSVLoad>(GetStage()->GetSharedObject(L"CSVLoad"));
		auto& data = csvLoad->GetPictureData();
		//目標のデータを探す
		int index = Utility::SearchDataIndex(data, m_texName);
		if (index == -1) {
			throw BaseException(
				L"目標のデータが見つかりません",
				L"texName : " + m_texName,
				L"Picture::OnCreate()"
			);
		}
		auto dat = data[index];
		Vec2 origin(0.0f);
		auto size = dat.size;
		auto rate = size.y / size.x;
		size.y = rate;
		size.x = 1.0f;
		Rect2D<float> pos;
		auto halfWidth = size.x / 2.0f;
		auto halfHeight = size.y / 2.0f;
		//色のデータ(R,G,B,A)
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		//頂点のデータ (番号は左上から右下まで)
		vector<VertexPositionColorTexture> vertices = {
			{Vec3(-halfWidth,halfHeight,0.0f),color,Vec2(0.0f,0.0f)}, //0
			{Vec3(halfWidth,halfHeight,0.0f),color,Vec2(1.0f,0.0f)}, //1

			{Vec3(-halfWidth,-halfHeight,0.0f),color,Vec2(0.0f,1.0f)}, //2
			{Vec3(halfWidth,-halfHeight,0.0f),color,Vec2(1.0f,1.0f)},  //3
		};
		//頂点インデックス
		vector<uint16_t> indices = {
			0, 1, 2, //上の三角形
			2, 1, 3 //下の三角形
		};

		//PNTだとテクスチャが反映されないのでPCTにしている
		auto drawComp = AddComponent<PCTStaticDraw>();
		//頂点データと頂点インデックスをもとにメッシュ(ポリゴン)を生成する
		drawComp->CreateOriginalMesh(vertices, indices);
		//自作したメッシュを使用する
		drawComp->SetOriginalMeshUse(true);

		drawComp->SetSamplerState(SamplerState::AnisotropicWrap); //テクスチャの繰り返し設定(Wrap)
		drawComp->SetDepthStencilState(DepthStencilState::Read);
		drawComp->SetTextureResource(m_texName);

		SetAlphaActive(true); //透明をサポートする&両面描画になる

		StageObject::OnCreate();
	}
}
//end basecross
