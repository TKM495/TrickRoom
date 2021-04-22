/*!
@file Stairs.cpp
@brief �K�i����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Stairs::Stairs(const shared_ptr<Stage>& stage,
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
		m_trickFlg = tokens[11] == L"TRUE" ? true : false;
		m_activeState = tokens[12] == L"Right" ? state::Right : state::Left;
	}

	void Stairs::OnCreate() {
		StageObject::OnCreate();
		if (m_trickFlg) {
			auto trick = AddComponent<TrickArtDraw>();
			trick->SetMeshResource(L"Stairs");
			trick->SetDir(m_activeState);

		}
		else {
			//�e������i�V���h�E�}�b�v��`�悷��j
			auto shadowPtr = AddComponent<Shadowmap>();
			//�e�̌`�i���b�V���j��ݒ�
			shadowPtr->SetMeshResource(L"Stairs");
			if (m_bProjActive) {
				auto ptrDraw = AddComponent<PNTStaticDraw2>();
				ptrDraw->SetMeshResource(L"Stairs");
				ptrDraw->SetOwnShadowActive(true);
			}
			else {
				auto ptrDraw = AddComponent<PNTStaticModelDraw>();
				ptrDraw->SetMeshResource(L"Stairs");
				ptrDraw->SetOwnShadowActive(true);
			}
		}

		auto stage = GetStage();
		//�Ζʗp�̃R���W����
		auto coll = stage->AddGameObject<AdvCollision>(GetThis<Stairs>(),
			Vec3(0.0f, 0.5f, -0.5f),
			Vec3(1.0f, sqrtf(5.0f), 1.0f),
			Vec3(XMConvertToRadians(90.0f - 26.56f), 0.0f, 0.0f),
			AdvCollision::Shape::Rect);
		m_myCols.push_back(coll);
		coll = stage->AddGameObject<AdvCollision>(GetThis<Stairs>(),
			Vec3(0.0f, 0.125f, 0.0f),
			Vec3(1.0f, 0.25f, 1.0f),
			Vec3(0.0f),
			AdvCollision::Shape::Obb);
		m_myCols.push_back(coll);
	}

	void Stairs::OnUpdate() {

	}
}
//end basecross
