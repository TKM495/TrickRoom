/*!
@file TrickArtDraw.h
@brief トリックアートの見た目を決めるシェーダー
*/

#pragma once
#include "stdafx.h"
#include "TrickArtBase.h"

namespace basecross {
    DECLARE_DX11_CONSTANT_BUFFER(CBTrickArt, SimpleConstants)
    DECLARE_DX11_VERTEX_SHADER(VSPNTTrickArt, VertexPositionNormalTexture)
    DECLARE_DX11_PIXEL_SHADER(PSPNTTrickArt)

    DECLARE_DX11_VERTEX_SHADER(VSPCTTrickArt, VertexPositionColorTexture)
    DECLARE_DX11_PIXEL_SHADER(PSPCTTrickArt)

    class TrickArtDraw :public SmBaseDraw, public TrickArtBase {
        struct Impl;
        unique_ptr<Impl> pImpl;

        bool m_flg;
        bool m_isPCT;

        void DrawStatic2(const MeshPrimData& data);
        void SetConstants2(SimpleConstants& SmCb, const MeshPrimData& data);
    public:
        TrickArtDraw(const shared_ptr<GameObject>& GameObjectPtr);
        virtual ~TrickArtDraw();

        void Active() {
            m_flg = true;
        }
        void OnCreate()override;
        void OnUpdate()override {}
        void OnDraw()override;

        void IsPCTModel(bool flg) {
            m_isPCT = flg;
        }

        Vec3 GetDirValue() {
            return TrickArtBase::GetMyDirValue();
        }
    };
}
//end basecross