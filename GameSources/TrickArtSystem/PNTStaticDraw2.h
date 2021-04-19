/*!
@file PNTStaticDraw2.h
@brief トリックアート描画に対応したシェーダー
*/

#pragma once
#include "stdafx.h"
#include "TrickArtSystem.h"

namespace basecross {
	struct SimpleConstantsEX
	{
		/// ワールド行列
		Mat4x4 World;
		/// ビュー行列
		Mat4x4 View;
		/// 射影行列
		Mat4x4 Projection;
		/// エミッシブ色
		Col4 Emissive;
		/// デフューズ色
		Col4 Diffuse;
		/// スペキュラー
		Col4 Specular;
		/// テクスチャ=xがアクティブかどうか
		XMUINT4 ActiveFlg;
		/// ライト方向
		Vec4 LightDir;
		/// ライト位置
		Vec4 LightPos;
		/// Eyeの位置
		Vec4 EyePos;
		/// ライトビュー行列
		Mat4x4 LightView;
		/// ライト射影行列
		Mat4x4 LightProjection;


		/// TAビュー行列
		Mat4x4 TAViewR;
		/// TAビュー行列
		Mat4x4 TAViewL;
		/// TA射影行列
		Mat4x4 TAProjection;

		SimpleConstantsEX() {
			memset(this, 0, sizeof(SimpleConstantsEX));
			Diffuse = Col4(1.0f, 1.0f, 1.0f, 1.0f);
		};
	};

    DECLARE_DX11_CONSTANT_BUFFER(CBPNTStaticDraw2, SimpleConstantsEX)
    DECLARE_DX11_VERTEX_SHADER(VSPNTStaticDraw2, VertexPositionNormalTexture)
    DECLARE_DX11_PIXEL_SHADER(PSPNTStaticDraw2)

    class PNTStaticDraw2 :public SmBaseDraw {
        void DrawStatic2(const MeshPrimData& data);
        void SetConstants2(SimpleConstantsEX& SmCb, const MeshPrimData& data);
    public:
        PNTStaticDraw2(const shared_ptr<GameObject>& GameObjectPtr);
        virtual ~PNTStaticDraw2();

        virtual void OnCreate()override;
        virtual void OnUpdate()override {}
        virtual void OnDraw()override;
    private:
        struct Impl;
        unique_ptr<Impl> pImpl;
    };
}
//end basecross