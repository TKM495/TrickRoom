/*!
@file Picture.cpp
@brief ���͋C���o�����߂̊G����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Picture::Picture(const shared_ptr<Stage>& stage,
		const wstring& line)
		:StageObject(stage)
	{
		vector<wstring> tokens;
		Util::WStrToTokenVector(tokens, line, L',');
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
		m_texName = tokens[10];
	}

	void Picture::OnCreate() {
		//CSVLoad���擾���f�[�^�����炤
		auto csvLoad = dynamic_pointer_cast<CSVLoad>(GetStage()->GetSharedObject(L"CSVLoad"));
		auto& data = csvLoad->GetPictureData();
		//�ڕW�̃f�[�^��T��
		int index = Utility::SearchDataIndex(data, m_texName);
		if (index == -1) {
			throw BaseException(
				L"�ڕW�̃f�[�^��������܂���",
				L"texName : " + m_texName,
				L"Picture::OnCreate()"
			);
		}
		auto dat = data[index];
		Vec2 origin(0.0f);
		auto size = dat.size;
		auto rate = size.y / size.x;
		size.y = rate;
		size.x = 1.0f;
		Rect2D<float> pos;
		auto halfWidth = size.x / 2.0f;
		auto halfHeight = size.y / 2.0f;
		//�F�̃f�[�^(R,G,B,A)
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		//���_�̃f�[�^ (�ԍ��͍��ォ��E���܂�)
		vector<VertexPositionColorTexture> vertices = {
			{Vec3(-halfWidth,halfHeight,0.0f),color,Vec2(0.0f,0.0f)}, //0
			{Vec3(halfWidth,halfHeight,0.0f),color,Vec2(1.0f,0.0f)}, //1

			{Vec3(-halfWidth,-halfHeight,0.0f),color,Vec2(0.0f,1.0f)}, //2
			{Vec3(halfWidth,-halfHeight,0.0f),color,Vec2(1.0f,1.0f)},  //3
		};
		//���_�C���f�b�N�X
		vector<uint16_t> indices = {
			0, 1, 2, //��̎O�p�`
			2, 1, 3 //���̎O�p�`
		};

		//PNT���ƃe�N�X�`�������f����Ȃ��̂�PCT�ɂ��Ă���
		auto drawComp = AddComponent<PCTStaticDraw>();
		//���_�f�[�^�ƒ��_�C���f�b�N�X�����ƂɃ��b�V��(�|���S��)�𐶐�����
		drawComp->CreateOriginalMesh(vertices, indices);
		//���삵�����b�V�����g�p����
		drawComp->SetOriginalMeshUse(true);

		drawComp->SetSamplerState(SamplerState::AnisotropicWrap); //�e�N�X�`���̌J��Ԃ��ݒ�(Wrap)
		drawComp->SetDepthStencilState(DepthStencilState::Read);
		drawComp->SetTextureResource(m_texName);

		SetAlphaActive(true); //�������T�|�[�g����&���ʕ`��ɂȂ�

		StageObject::OnCreate();
	}
}
//end basecross
