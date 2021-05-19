/*!
@file VirtualFloor.cpp
@brief ���z��(�e�N�X�`�����\��Ȃ��I�u�W�F�N�g�ɓ\��p)�N���X
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	VirtualFloor::VirtualFloor(const shared_ptr<Stage>& stage,
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
		m_bProjActive = tokens[10] == L"TRUE" ? true : false;
	}

	void VirtualFloor::OnCreate() {
		vector<Vec2> uv = {
			Vec2(0.0f,0.0f),
			Vec2(m_scale.x / 1.0f,0.0f),
			Vec2(0.0f,m_scale.z / 1.0f),
			Vec2(m_scale.x / 1.0f,m_scale.z / 1.0f)
		};

		//�F�̃f�[�^(R,G,B,A)
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		Vec3 up(-1.0f, 0.0f, 0.0f);
		//���_�̃f�[�^ (�ԍ��͍��ォ��E���܂�)
		//Z�ł͂Ȃ�Y���g���Ă���͓̂����蔻��̊֌W��
		vector<VertexPositionNormalTexture> vertices = {
			{Vec3(-0.5f, 0.0f, +0.5f),up,uv[0]}, //0
			{Vec3(+0.5f, 0.0f, +0.5f),up,uv[1]}, //1
			{Vec3(-0.5f, 0.0f, -0.5f),up,uv[2]}, //2
			{Vec3(+0.5f, 0.0f, -0.5f),up,uv[3]}  //3
		};
		//���_�C���f�b�N�X(���_���Ȃ��鏇��)
		std::vector<uint16_t> indices = {
			0, 1, 2, //��̎O�p�`
			2, 1, 3  //���̎O�p�`
		};

		shared_ptr<SmBaseDraw> ptrDraw;
		if (m_bProjActive) {
			ptrDraw = AddComponent<PNTStaticDraw2>();
		}
		else {
			ptrDraw = AddComponent<PNTStaticDraw>();
		}
		ptrDraw->SetOwnShadowActive(true);
		ptrDraw->CreateOriginalMesh(vertices, indices);
		ptrDraw->SetOriginalMeshUse(true);
		ptrDraw->SetTextureResource(L"Floor");

		ptrDraw->SetSamplerState(SamplerState::AnisotropicWrap);
		ptrDraw->SetDepthStencilState(DepthStencilState::Read);

		StageObject::ObjectSetUp();
	}
}
//end basecross