/*!
@file TrickArtDraw.h
@brief トリックアートの見た目を決めるシェーダー
*/

#pragma once
#include "stdafx.h"
#include "TrickArtBase.h"

namespace basecross {
    DECLARE_DX11_CONSTANT_BUFFER(CBTrickArt, SimpleConstants)
    DECLARE_DX11_VERTEX_SHADER(VSTrickArt, VertexPositionNormalTexture)
    DECLARE_DX11_PIXEL_SHADER(PSTrickArt)

    class TrickArtDraw :public SmBaseDraw, public TrickArtBase {
        struct Impl;
        unique_ptr<Impl> pImpl;

        bool m_flg;

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

        Vec3 GetDirValue() {
            return TrickArtBase::GetMyDirValue();
        }
    };
}
//end basecross