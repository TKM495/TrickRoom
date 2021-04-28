/*!
@file Cursor.cpp
@brief ���j���[�p�̃J�[�\���N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Cursor::OnCreate() {
		vector<Vec3> pos;
		if (m_name == L"VCursor") {
			pos = {
				Vec3(-300.0f, +50.0f,0.0f),
				Vec3(+300.0f, +50.0f,0.0f),
				Vec3(-300.0f, -50.0f,0.0f),
				Vec3(+300.0f, -50.0f,0.0f)
			};
			m_color = Col4(1.0f, 1.0f, 1.0f, 0.3f);
		}
		else if (m_name == L"SelectCursor") {
			auto size = Utility::GetTextureSize(m_name);
			auto widthHalf = size.x / 2.0f;
			auto heightHalf = size.y / 2.0f;
			pos = {
				Vec3(-widthHalf, +heightHalf,0.0f),
				Vec3(+widthHalf, +heightHalf,0.0f),
				Vec3(-widthHalf, -heightHalf,0.0f),
				Vec3(+widthHalf, -heightHalf,0.0f)
			};
			m_color = Col4(1.0f, 1.0f, 0.0f, 1.0f);
			//SetUpdateActive(false);
		}

		//�F�̃f�[�^(R,G,B,A)
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		//���_�̃f�[�^ (�ԍ��͍��ォ��E���܂�)
		vector<VertexPositionColorTexture> vertices = {
			{pos[0],color,Vec2(0.0f,0.0f)}, //0
			{pos[1],color,Vec2(1.0f,0.0f)}, //1
			{pos[2],color,Vec2(0.0f,1.0f)}, //2
			{pos[3],color,Vec2(1.0f,1.0f)},  //3
		};
		//���_�C���f�b�N�X(���_���Ȃ��鏇��)
		std::vector<uint16_t> indices = {
			0, 1, 2, //��̎O�p�`
			2, 1, 3  //���̎O�p�`
		};

		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);

		drawComp->SetSamplerState(SamplerState::AnisotropicWrap); //�e�N�X�`���̌J��Ԃ��ݒ�(Wrap)
		drawComp->SetDepthStencilState(DepthStencilState::Read);
		drawComp->SetTextureResource(m_name);
		drawComp->SetDiffuse(m_color);

		SetAlphaActive(true);
		SetDrawLayer(3);
	}

	void Cursor::OnUpdate() {
		auto delta = App::GetApp()->GetElapsedTime();

		auto time = sinf(m_delta);

		auto alpha = Lerp::CalculateLerp(m_min, m_max, -1.0f, 1.0f, time, Lerp::rate::Linear);

		auto drawComp = GetComponent<PCTSpriteDraw>();
		Col4 color = m_color;
		color.w = alpha;
		drawComp->SetDiffuse(color);

		m_delta += delta * m_rate;
		if (m_delta >= XM_2PI) {
			m_delta = 0.0f;
		}
	}
}
//end basecross
