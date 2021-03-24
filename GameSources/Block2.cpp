/*!
@file Block2.cpp
@brief ブロック実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class Block : public GameObject;
	//--------------------------------------------------------------------------------------
	//構築と破棄
	Block::Block(const shared_ptr<Stage>& StagePtr,
		const wstring& line
	) :
		StageObject(StagePtr)
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
	Block::~Block() {}

	//初期化
	void Block::OnCreate() {
		StageObject::OnCreate();

		//OBB衝突j判定を付ける
		auto ptrColl = AddComponent<CollisionObb>();
		ptrColl->SetFixed(true);
		ptrColl->SetDrawActive(true);
		//タグをつける
		//AddTag(L"FixedBox");
		//影をつける（シャドウマップを描画する）
		//auto shadowPtr = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		//shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
		//ptrDraw->SetTextureResource(L"SKY_TX");
		//ptrDraw->SetFogEnabled(true);
		//ptrDraw->SetOwnShadowActive(true);
	}
}
//end basecross
