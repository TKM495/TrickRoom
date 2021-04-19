/*!
@file PNTStaticDraw2.h
@brief �g���b�N�A�[�g�`��ɑΉ������V�F�[�_�[
*/

#pragma once
#include "stdafx.h"
#include "TrickArtSystem.h"

namespace basecross {
	struct SimpleConstantsEX
	{
		/// ���[���h�s��
		Mat4x4 World;
		/// �r���[�s��
		Mat4x4 View;
		/// �ˉe�s��
		Mat4x4 Projection;
		/// �G�~�b�V�u�F
		Col4 Emissive;
		/// �f�t���[�Y�F
		Col4 Diffuse;
		/// �X�y�L�����[
		Col4 Specular;
		/// �e�N�X�`��=x���A�N�e�B�u���ǂ���
		XMUINT4 ActiveFlg;
		/// ���C�g����
		Vec4 LightDir;
		/// ���C�g�ʒu
		Vec4 LightPos;
		/// Eye�̈ʒu
		Vec4 EyePos;
		/// ���C�g�r���[�s��
		Mat4x4 LightView;
		/// ���C�g�ˉe�s��
		Mat4x4 LightProjection;


		/// TA�r���[�s��
		Mat4x4 TAViewR;
		/// TA�r���[�s��
		Mat4x4 TAViewL;
		/// TA�ˉe�s��
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