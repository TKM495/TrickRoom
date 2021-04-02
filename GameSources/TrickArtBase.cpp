/*!
@file TrickArtBase.cpp
@brief トリックアートの基底クラスの実態
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TrickArtBase::OnCreate() {

		auto drawComp = AddComponent<PCTStaticDraw>();
		//頂点データと頂点インデックスをもとにメッシュ(ポリゴン)を生成する
		drawComp->CreateOriginalMesh(m_vertices, m_indices);
		//自作したメッシュを使用する
		drawComp->SetOriginalMeshUse(true);

		drawComp->SetSamplerState(SamplerState::AnisotropicWrap); //テクスチャの繰り返し設定(Wrap)
		drawComp->SetDepthStencilState(DepthStencilState::Read);
		drawComp->SetTextureResource(m_texStr);

		SetAlphaActive(true); //透明をサポートする&両面描画になる

		StageObject::OnCreate();
	}

	void TrickArtBase::OnUpdate() {

	}
}
//end basecross
