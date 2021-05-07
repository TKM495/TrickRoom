/*!
@file PNTStaticDraw2.h
@brief �g���b�N�A�[�g�`��ɑΉ������V�F�[�_�[
*/

#pragma once
#include "stdafx.h"
#include "TrickArtSystem.h"

namespace basecross {
	struct SimpleConstantsEXTitle
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
		Mat4x4 TAView;
		/// TA�ˉe�s��
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