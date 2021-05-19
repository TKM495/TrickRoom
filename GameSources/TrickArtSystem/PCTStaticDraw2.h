/*!
@file PCTStaticDraw2.h
@brief トリックアート描画に対応したシェーダー(ライティングなし)
*/

#pragma once
#include "stdafx.h"
#include "TrickArtSystem.h"

namespace basecross {
	DECLARE_DX11_CONSTANT_BUFFER(CBPCTStaticDraw2, SimpleConstantsEX)
	DECLARE_DX11_VERTEX_SHADER(VSPCTStaticDraw2, VertexPositionColorTexture)
	DECLARE_DX11_PIXEL_SHADER(PSPCTStaticDraw2)

	class PCTStaticDraw2 :public SmBaseDraw {
		void DrawStatic2(const MeshPrimData& data);
		void SetConstants2(SimpleConstantsEX& SmCb, const MeshPrimData& data);
	public:
		PCTStaticDraw2(const shared_ptr<GameObject>& GameObjectPtr);
		virtual ~PCTStaticDraw2();

		virtual void OnCreate()override;
		virtual void OnUpdate()override {}
		virtual void OnDraw()override;
	private:
		struct Impl;
		unique_ptr<Impl> pImpl;
	};
}
//end basecross