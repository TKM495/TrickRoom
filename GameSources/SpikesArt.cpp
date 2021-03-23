/*!
@file SpikesArt.cpp
@brief �g���b�N�A�[�g�̞��N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void SpikesArt::OnCreate() {
		m_position = Vec3(0.0f,-0.49f,0.0f);
		m_scale = Vec3(1.0f);

		auto halfSize = m_artSize / 2.0f;

		//�F�̃f�[�^(R,G,B,A)
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		//���_�̃f�[�^ (�ԍ��͍��ォ��E���܂�)
		vector<VertexPositionColorTexture> vertices = {
			{Vec3(-halfSize, 0.0f,+halfSize),color,Vec2(0.0f,0.4f)}, //0
			{Vec3(+halfSize, 0.0f,+halfSize),color,Vec2(1.0f,0.4f)}, //1
			{Vec3(-halfSize, 0.0f,-halfSize),color,Vec2(0.0f,1.0f)}, //2
			{Vec3(+halfSize, 0.0f,-halfSize),color,Vec2(1.0f,1.0f)}  //3
		};
		//���_�C���f�b�N�X(���_���Ȃ��鏇��)
		std::vector<uint16_t> indices = {
			0, 1, 2, //��̎O�p�`
			2, 1, 3  //���̎O�p�`
		};

		auto drawComp = AddComponent<PCTStaticDraw>();
		//���_�f�[�^�ƒ��_�C���f�b�N�X�����ƂɃ��b�V��(�|���S��)�𐶐�����
		drawComp->CreateOriginalMesh(vertices, indices);
		//���삵�����b�V�����g�p����
		drawComp->SetOriginalMeshUse(true);
		drawComp->SetTextureResource(L"SpikesArt");

		drawComp->SetSamplerState(SamplerState::AnisotropicWrap); //�e�N�X�`���̌J��Ԃ��ݒ�(Wrap)
		drawComp->SetDepthStencilState(DepthStencilState::Read);

		SetAlphaActive(true); //�������T�|�[�g����&���ʕ`��ɂȂ�



			auto obbComp = AddComponent<CollisionObb>();
			obbComp->SetFixed(true);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		transComp->SetScale(m_scale);
		transComp->SetRotation(0.0f, XMConvertToRadians(-45.0f),0.0f);

		//�����蔻��̐؂�ւ��Ń_���[�W�̔�����s������
		//��ɂ��̃^�O������
		AddTag(L"damege");
	}
}
//end basecross