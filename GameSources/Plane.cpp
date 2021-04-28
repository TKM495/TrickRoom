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
		m_bProjActive = tokens[10] == L"TRUE" ? true : false;

		m_bNotTexture = tokens[11] == L"TRUE" ? true : false;

		//���̎�(���͕K��90���ɂȂ�̂�)
		if ((float)_wtof(tokens[7].c_str()) == 90.0f) {
			AddTag(L"Floor");
			m_texName = L"Floor";
		}
		else {
			AddTag(L"Wall");
			m_texName = L"Wall";
		}
	}

	void Plane::OnCreate() {

		vector<Vec2> uv;
		if (m_texName == L"Floor") {
			uv = {
				Vec2(0.0f,0.0f),
				Vec2(m_scale.x / 2.0f,0.0f),
				Vec2(0.0f,m_scale.y / 2.0f),
				Vec2(m_scale.x / 2.0f,m_scale.y / 2.0f)
			};
		}
		else if (m_texName == L"Wall") {
			uv = {
				Vec2(0.0f,0.0f),
				Vec2(m_scale.x,0.0f),
				Vec2(0.0f,1.0f),
				Vec2(m_scale.x,1.0f)
			};
		}
		//�F�̃f�[�^(R,G,B,A)
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		Vec3 up(-1.0f, 0.0f, 0.0f);
		//���_�̃f�[�^ (�ԍ��͍��ォ��E���܂�)
		//Z�ł͂Ȃ�Y���g���Ă���͓̂����蔻��̊֌W��
		vector<VertexPositionNormalTexture> vertices = {
			{Vec3(-0.5f, +0.5f, 0.0f),up,uv[0]}, //0
			{Vec3(+0.5f, +0.5f, 0.0f),up,uv[1]}, //1
			{Vec3(-0.5f, -0.5f, 0.0f),up,uv[2]}, //2
			{Vec3(+0.5f, -0.5f, 0.0f),up,uv[3]}  //3
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
		if (!m_bNotTexture) {
			auto scene = App::GetApp()->GetScene<Scene>();
			wstring num;
			switch (scene->GetStageNum())
			{
			case 1:
			case 2:
			case 3:
				num = L"1";
				break;
			case 4:
			case 5:
			case 6:
				num = L"2";
				break;
			case 7:
			case 8:
			case 9:
				num = L"3";
				break;
			case 10:
				num = L"4";
				break;
			default:
				num = L"1";
				break;
			}
			if (m_texName == L"Floor") {
				num = L"";
			}
			ptrDraw->SetTextureResource(m_texName + num);
		}
		ptrDraw->SetSamplerState(SamplerState::AnisotropicWrap);
		ptrDraw->SetDepthStencilState(DepthStencilState::Read);

		StageObject::OnCreate();

		auto collComp = AddComponent<CollisionRect>();
		collComp->SetFixed(true);
		auto scene = App::GetApp()->GetScene<Scene>();
		if (scene->GetDebugState() == DebugState::Debug) {
			collComp->SetDrawActive(true);
		}

		//drawComp->SetSamplerState(SamplerState::AnisotropicWrap); //�e�N�X�`���̌J��Ԃ��ݒ�(Wrap)
		//drawComp->SetDepthStencilState(DepthStencilState::Read);
	}
}
//end basecross
