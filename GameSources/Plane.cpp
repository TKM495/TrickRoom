/*!
@file Plane.cpp
@brief �I�u�W�F�N�g����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Plane::Plane(shared_ptr<Stage>& stage,
		const wstring& line)
		:StageObject(stage)
	{
		//�g�[�N���i�J�����j�̔z��
		vector<wstring> tokens;
		Util::WStrToTokenVector(tokens, line, L',');
		//�e�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
		m_position = Vec3(
			(float)_wtof(tokens[1].c_str()),
			(float)_wtof(tokens[2].c_str()),
			(float)_wtof(tokens[3].c_str())
		);
		m_scale = Vec3(
			(float)_wtof(tokens[4].c_str()),
			(float)_wtof(tokens[5].c_str()),
			(float)_wtof(tokens[6].c_str())
		);
		m_rotation = Vec3(
			XMConvertToRadians((float)_wtof(tokens[7].c_str())),
			XMConvertToRadians((float)_wtof(tokens[8].c_str())),
			XMConvertToRadians((float)_wtof(tokens[9].c_str()))
		);
	}


	void Plane::OnCreate() {
		//�F�̃f�[�^(R,G,B,A)
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		//���_�̃f�[�^ (�ԍ��͍��ォ��E���܂�)
		vector<VertexPositionColorTexture> vertices = {
			{Vec3(-0.5f, +0.5f, 0.0f),color,Vec2(0.0f,0.0f)}, //0
			{Vec3(+0.5f, +0.5f, 0.0f),color,Vec2(1.0f,0.0f)}, //1
			{Vec3(-0.5f, -0.5f, 0.0f),color,Vec2(0.0f,1.0f)}, //2
			{Vec3(+0.5f, -0.5f, 0.0f),color,Vec2(1.0f,1.0f)}  //3
		};
		//���_�C���f�b�N�X(���_���Ȃ��鏇��)
		std::vector<uint16_t> indices = {
			0, 1, 2, //��̎O�p�`
			2, 1, 3  //���̎O�p�`
		};
		auto collComp = AddComponent<CollisionRect>();
		collComp->SetFixed(true);

		auto drawComp = AddComponent<BcPNTStaticDraw>();
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
		transComp->SetRotation(m_rotation);
	}
}
//end basecross
