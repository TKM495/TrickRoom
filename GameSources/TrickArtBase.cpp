/*!
@file TrickArtBase.cpp
@brief トリックアートの基底クラスの実態
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//void TrickArtBase::OnCreate() {
	//	//色のデータ(R,G,B,A)
	//	Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
	//	//頂点のデータ (番号は左上から右下まで)
	//	//Vec3:頂点位置(ローカル座標(メッシュ内の座標)(0,0,0)がピボットポイントになる)
	//	//Col4:頂点の色(「ポリゴンの色」×「テクスチャの色」(乗算))
	//	//Vec2:UV座標位置(左上を0,0として右下を1,1とする座標(画像サイズに関係ない))
	//	vertices = {
	//		{Vec3(-1.0f, +1.0f,0.0f),color,Vec2(0.0f,0.0f)}, //0
	//		{Vec3(+1.0f, +1.0f,0.0f),color,Vec2(1.0f,0.0f)}, //1

	//		{Vec3(-1.0f, 0.0f,0.0f),color,Vec2(0.0f,0.5f)}, //2
	//		{Vec3(+1.0f, 0.0f,0.0f),color,Vec2(1.0f,0.5f)},  //3

	//		{Vec3(-1.0f, -1.0f,0.0f),color,Vec2(0.0f,1.0f)}, //4
	//		{Vec3(+1.0f, -1.0f,0.0f),color,Vec2(1.0f,1.0f)}  //5
	//	};
	//	//頂点インデックス(頂点をつなげる順番)
	//	//ポリゴンの裏表はつなげる順番(右回りに見える方向が表)で決まる
	//	std::vector<uint16_t> indices = {
	//		0, 1, 2, //上の三角形
	//		2, 1, 3, //下の三角形
	//		2, 3, 4,
	//		4, 3, 5
	//	};

	//	auto drawComp = AddComponent<PCTStaticDraw>();
	//	//頂点データと頂点インデックスをもとにメッシュ(ポリゴン)を生成する
	//	drawComp->CreateOriginalMesh(vertices, indices);
	//	//自作したメッシュを使用する
	//	drawComp->SetOriginalMeshUse(true);

	//	drawComp->SetSamplerState(SamplerState::AnisotropicWrap); //テクスチャの繰り返し設定(Wrap)
	//	drawComp->SetDepthStencilState(DepthStencilState::Read);

	//	//SetAlphaActive(true); //透明をサポートする&両面描画になる

	//	auto transComp = GetComponent<Transform>();
	//	transComp->SetPosition(m_position);
	//	transComp->SetScale(m_scale);
	//}

}
//end basecross
