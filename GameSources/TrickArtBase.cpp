/*!
@file TrickArtBase.cpp
@brief �g���b�N�A�[�g�̊��N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//void TrickArtBase::OnCreate() {
	//	//�F�̃f�[�^(R,G,B,A)
	//	Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
	//	//���_�̃f�[�^ (�ԍ��͍��ォ��E���܂�)
	//	//Vec3:���_�ʒu(���[�J�����W(���b�V�����̍��W)(0,0,0)���s�{�b�g�|�C���g�ɂȂ�)
	//	//Col4:���_�̐F(�u�|���S���̐F�v�~�u�e�N�X�`���̐F�v(��Z))
	//	//Vec2:UV���W�ʒu(�����0,0�Ƃ��ĉE����1,1�Ƃ�����W(�摜�T�C�Y�Ɋ֌W�Ȃ�))
	//	vertices = {
	//		{Vec3(-1.0f, +1.0f,0.0f),color,Vec2(0.0f,0.0f)}, //0
	//		{Vec3(+1.0f, +1.0f,0.0f),color,Vec2(1.0f,0.0f)}, //1

	//		{Vec3(-1.0f, 0.0f,0.0f),color,Vec2(0.0f,0.5f)}, //2
	//		{Vec3(+1.0f, 0.0f,0.0f),color,Vec2(1.0f,0.5f)},  //3

	//		{Vec3(-1.0f, -1.0f,0.0f),color,Vec2(0.0f,1.0f)}, //4
	//		{Vec3(+1.0f, -1.0f,0.0f),color,Vec2(1.0f,1.0f)}  //5
	//	};
	//	//���_�C���f�b�N�X(���_���Ȃ��鏇��)
	//	//�|���S���̗��\�͂Ȃ��鏇��(�E���Ɍ�����������\)�Ō��܂�
	//	std::vector<uint16_t> indices = {
	//		0, 1, 2, //��̎O�p�`
	//		2, 1, 3, //���̎O�p�`
	//		2, 3, 4,
	//		4, 3, 5
	//	};

	//	auto drawComp = AddComponent<PCTStaticDraw>();
	//	//���_�f�[�^�ƒ��_�C���f�b�N�X�����ƂɃ��b�V��(�|���S��)�𐶐�����
	//	drawComp->CreateOriginalMesh(vertices, indices);
	//	//���삵�����b�V�����g�p����
	//	drawComp->SetOriginalMeshUse(true);

	//	drawComp->SetSamplerState(SamplerState::AnisotropicWrap); //�e�N�X�`���̌J��Ԃ��ݒ�(Wrap)
	//	drawComp->SetDepthStencilState(DepthStencilState::Read);

	//	//SetAlphaActive(true); //�������T�|�[�g����&���ʕ`��ɂȂ�

	//	auto transComp = GetComponent<Transform>();
	//	transComp->SetPosition(m_position);
	//	transComp->SetScale(m_scale);
	//}

}
//end basecross
