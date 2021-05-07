/*!
@file PNTStaticDraw2.h
@brief トリックアート描画に対応したシェーダー
*/

#pragma once
#include "stdafx.h"
#include "TrickArtSystem.h"

namespace basecross {
	struct SimpleConstantsEXTitle
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
		Mat4x4 TAView;
		/// TA射影行列
		Mat4x4 TAProjection;

		SimpleConstantsEXTitle() {
			memset(this, 0, sizeof(SimpleConstantsEXTitle));
			Diffuse = Col4(1.0f, 1.0f, 1.0f, 1.0f);
		};
	};

	DECLARE_DX11_CONSTANT_BUFFER(CBPNTStaticDraw2Title, SimpleConstantsEXTitle)
	DECLARE_DX11_VERTEX_SHADER(VSPNTStaticDraw2Title, VertexPositionNormalTexture)
	DECLARE_DX11_PIXEL_SHADER(PSPNTStaticDraw2Title)

    class PNTStaticDraw2Title :public SmBaseDraw {
        void DrawStatic2(const MeshPrimData& data);
        void SetConstants2(SimpleConstantsEXTitle& SmCb, const MeshPrimData& data);
    public:
        PNTStaticDraw2Title(const shared_ptr<GameObject>& GameObjectPtr);
        virtual ~PNTStaticDraw2Title();

        virtual void OnCreate()override;
        virtual void OnUpdate()override {}
        virtual void OnDraw()override;

        void SetDefPos(Vec3 pos) {
            m_defPos = pos;
        }
    private:
        Vec3 m_defPos;
        struct Impl;
        unique_ptr<Impl> pImpl;
    };
}
//end basecross