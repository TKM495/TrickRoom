/*!
@file Plane.cpp
@brief �I�u�W�F�N�g����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Plane::OnCreate() {
		//�F�̃f�[�^(R,G,B,A)
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		//���_�̃f�[�^ (�ԍ��͍��ォ��E���܂�)
		vector<VertexPositionColorTexture> vertices = {
			{Vec3(-0.5f, 0.0f,+0.5f),color,Vec2(0.0f,0.0f)}, //0
			{Vec3(+0.5f, 0.0f,+0.5f),color,Vec2(1.0f,0.0f)}, //1
			{Vec3(-0.5f, 0.0f,-0.5f),color,Vec2(0.0f,1.0f)}, //2
			{Vec3(+0.5f, 0.0f,-0.5f),color,Vec2(1.0f,1.0f)}  //3
		};
		//���_�C���f�b�N�X(���_���Ȃ��鏇��)
		std::vector<uint16_t> indices = {
			0, 1, 2, //��̎O�p�`
			2, 1, 3  //���̎O�p�`
		};

		auto collComp = AddComponent<CollisionObb>();
		collComp->SetFixed(true);

		auto drawComp = AddComponent<PCTStaticDraw>();
		//���_�f�[�^�ƒ��_�C���f�b�N�X�����ƂɃ��b�V��(�|���S��)�𐶐�����
		drawComp->CreateOriginalMesh(vertices, indices);
		//���삵�����b�V�����g�p����
		drawComp->SetOriginalMeshUse(true);
		//drawComp->SetTextureResource(L"SpikesArt");

		//drawComp->SetSamplerState(SamplerState::AnisotropicWrap); //�e�N�X�`���̌J��Ԃ��ݒ�(Wrap)
		//drawComp->SetDepthStencilState(DepthStencilState::Read);

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		transComp->SetScale(m_scale);
	}
}
//end basecross
