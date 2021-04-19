/*!
@file FloorArt.cpp
@brief ���̃g���b�N�A�[�g����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	FloorArt::FloorArt(const shared_ptr<Stage>& stage,
		const wstring& line)
		:TrickArtBaseOld(stage)
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

	void FloorArt::OnCreate() {
		//�F�̃f�[�^(R,G,B,A)
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		//���_�̃f�[�^ (�ԍ��͍��ォ��E���܂�)
		m_vertices = {
			{Vec3(-2.61468,1.56666,0),color,Vec2(0.0f,0.0f)}, //0
			{Vec3(2.52899,2.87567,0),color,Vec2(1.0f,0.0f)}, //1
			{Vec3(-2.19189,-2.6186,0),color,Vec2(0.0f,1.0f)}, //2
			{Vec3(2.43245,-1.44531,0),color,Vec2(1.0f,1.0f)}  //3
		};
		//���_�C���f�b�N�X(���_���Ȃ��鏇��)
		m_indices = {
			0, 1, 2, //��̎O�p�`
			2, 1, 3  //���̎O�p�`
		};

		TrickArtBaseOld::OnCreate();

		auto stage = GetStage();
		//�Ζʗp�̃R���W����
		auto coll = stage->AddGameObject<AdvCollision>(GetThis<FloorArt>(),
			Vec3(0.25f, 0.2f, -0.25f),
			Vec3(3.5f, 0.5f, 0.8f),
			Vec3(0.0f, 0.0f, XMConvertToRadians(-10.0f)),
			AdvCollision::Shape::Obb);
		m_myCols.push_back(coll);
	}

	void FloorArt::OnUpdate() {
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
