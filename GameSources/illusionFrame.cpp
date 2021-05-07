/*!
@file illusionFrame.cpp
@brief �����t���[���̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void illusionFrame::SetPosition(Vec2 pos) {
		GetComponent<Transform>()->SetPosition((Vec3)pos);
	}

	void illusionFrame::OnCreate() {
		auto texSize = Utility::GetTextureSize(m_texName);

		Col4 color(1.0f);
		auto halfWidth = texSize.x / 2.0f;
		auto halfHeight = texSize.y / 8.0f; //���̃e�N�X�`����3�Z�b�g�Ȃ̂Ŕ����̔����̔����̔���
		vertices = {
			{Vec3(-halfWidth, +halfHeight, 0.0f),color,Vec2(0.0f,0.25f)},  //0
			{Vec3(+halfWidth, +halfHeight, 0.0f),color,Vec2(1.0f,0.25f)},  //1
			{Vec3(-halfWidth, -halfHeight, 0.0f),color,Vec2(0.0f,0.5f)},  //2
			{Vec3(+halfWidth, -halfHeight, 0.0f),color,Vec2(1.0f,0.5f)},  //3
		};
		//���_�C���f�b�N�X
		vector<uint16_t> indices = {
			0, 1, 2,
			2, 1, 3
		};

		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);
		drawComp->SetTextureResource(m_texName);
		drawComp->SetSamplerState(SamplerState::AnisotropicWrap); //�e�N�X�`���̌J��Ԃ��ݒ�(Wrap)
		drawComp->SetDepthStencilState(DepthStencilState::Read);

		SetAlphaActive(true); //�������T�|�[�g����&���ʕ`��ɂȂ�
	}

	void illusionFrame::SetFrameActive(Status stat) {
		vector<Vec2> uv;
		switch (stat)
		{
		case Status::Active:
			uv = {
				Vec2(0.0f,0.0f),
				Vec2(1.0f,0.0f),
				Vec2(0.0f,0.25f),
				Vec2(1.0f,0.25f)
			};
			break;
		case Status::Invalid:
			uv = {
				Vec2(0.0f,0.25f),
				Vec2(1.0f,0.25f),
				Vec2(0.0f,0.5f),
				Vec2(1.0f,0.5f)
			};
			break;
		case Status::Neutral:
			uv = {
				Vec2(0.0f,0.5f),
				Vec2(1.0f,0.5f),
				Vec2(0.0f,0.75f),
				Vec2(1.0f,0.75f)
			};
			break;
		default:
			//�G���[
			break;
		}
		for (int i = 0; i < vertices.size(); i++) {
			vertices[i].textureCoordinate = uv[i];
		}
		GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
	}
}
//end basecross