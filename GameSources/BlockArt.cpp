/*!
@file BlockArt.cpp
@brief �u���b�N�g���b�N�A�[�g����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	BlockArt::BlockArt(const shared_ptr<Stage>& stage,
		const wstring& line)
		:TrickArtBase(stage)
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
		m_activeState = tokens[10] == L"Right" ? state::Right : state::Left;
		m_texStr = tokens[11].c_str();
	}


	void BlockArt::OnCreate() {
		auto halfSize = 5.0f / 2.0f;

		//�F�̃f�[�^(R,G,B,A)
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		//���_�̃f�[�^ (�ԍ��͍��ォ��E���܂�)
		m_vertices = {
			{Vec3(-halfSize, 0.0f,+halfSize),color,Vec2(0.0f,0.1f)}, //0
			{Vec3(+halfSize, 0.0f,+halfSize),color,Vec2(1.0f,0.1f)}, //1
			{Vec3(-halfSize, 0.0f,-halfSize),color,Vec2(0.0f,0.9f)}, //2
			{Vec3(+halfSize, 0.0f,-halfSize),color,Vec2(1.0f,0.9f)}  //3
		};
		//���_�C���f�b�N�X(���_���Ȃ��鏇��)
		m_indices = {
			0, 1, 2, //��̎O�p�`
			2, 1, 3  //���̎O�p�`
		};

		TrickArtBase::OnCreate();

		auto stage = GetStage();
		auto coll = stage->AddGameObject<AdvCollision>(GetThis<BlockArt>(),
			Vec3(0.0f, 0.5f, -0.7f),
			Vec3(1.0f, 1.0f, 4.0f),
			Vec3(0.0f, XMConvertToRadians(45.0f), 0.0f),
			AdvCollision::Shape::Obb);
		m_myCols.push_back(coll);
	}

	void BlockArt::OnUpdate() {
		auto camera = dynamic_pointer_cast<MainCamera>(OnGetDrawCamera());
		state nowState = camera->GetCamState();
		if (nowState == m_activeState) {
			for (auto& coll : m_myCols) {
				coll->SetActive(true);
			}
		}
		else {
			for (auto& coll : m_myCols) {
				coll->SetActive(false);
			}
		}
	}
}
//end basecross
