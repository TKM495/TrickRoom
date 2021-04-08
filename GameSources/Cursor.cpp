/*!
@file Cursor.cpp
@brief ���j���[�p�̃J�[�\���N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Cursor::OnCreate() {
		//�F�̃f�[�^(R,G,B,A)
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		//���_�̃f�[�^ (�ԍ��͍��ォ��E���܂�)
		vector<VertexPositionColorTexture> vertices = {
			{Vec3(-300.0f, +50.0f,0.0f),color,Vec2(0.0f,0.0f)}, //0
			{Vec3(+300.0f, +50.0f,0.0f),color,Vec2(1.0f,0.0f)}, //1

			{Vec3(-300.0f, -50.0f,0.0f),color,Vec2(0.0f,1.0f)}, //2
			{Vec3(+300.0f, -50.0f,0.0f),color,Vec2(1.0f,1.0f)},  //3
		};
		//���_�C���f�b�N�X(���_���Ȃ��鏇��)
		std::vector<uint16_t> indices = {
			0, 1, 2, //��̎O�p�`
			2, 1, 3  //���̎O�p�`
		};

		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);

		drawComp->SetSamplerState(SamplerState::AnisotropicWrap); //�e�N�X�`���̌J��Ԃ��ݒ�(Wrap)
		drawComp->SetDepthStencilState(DepthStencilState::Read);
		drawComp->SetTextureResource(L"VCursor");
		drawComp->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 0.3f));

		SetAlphaActive(true);
	}

}
//end basecross
