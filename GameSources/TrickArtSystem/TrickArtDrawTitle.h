/*!
@file TrickArtDraw.h
@brief トリックアートの見た目を決めるシェーダー
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    DECLARE_DX11_CONSTANT_BUFFER(CBTrickArtTitle, SimpleConstants)
    DECLARE_DX11_VERTEX_SHADER(VSTrickArtTitle, VertexPositionNormalTexture)
    DECLARE_DX11_PIXEL_SHADER(PSTrickArtTitle)

    class TrickArtDrawTitle :public SmBaseDraw {
        struct Impl;
        unique_ptr<Impl> pImpl;

        bool m_flg;
        Vec3 m_defPos;
        void DrawStatic2(const MeshPrimData& data);
        void SetConstants2(SimpleConstants& SmCb, const MeshPrimData& data);
    public:
        TrickArtDrawTitle(const shared_ptr<GameObject>& GameObjectPtr);
        virtual ~TrickArtDrawTitle();

        void Active() {
            m_flg = true;
        }
        void SetDefPos(Vec3 pos) {
            m_defPos = pos;
        }
        void OnCreate()override;
        void OnUpdate()override {}
        void OnDraw()override;
    };
}
//end basecross