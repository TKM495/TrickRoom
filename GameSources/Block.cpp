/*!
@file Block2.cpp
@brief �u���b�N����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class Block : public GameObject;
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	Block::Block(const shared_ptr<Stage>& StagePtr,
		const wstring& line)
		:StageObject(StagePtr)
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
	Block::~Block() {}

	//������
	void Block::OnCreate() {
		StageObject::OnCreate();

		if (m_trickFlg) {
			auto trick = AddComponent<TrickArtDraw>();
			trick->SetMeshResource(L"DEFAULT_CUBE");
			trick->SetDir(m_activeState);
			AddTag(L"TrickArtObj");
		}
		else {
			//�e������i�V���h�E�}�b�v��`�悷��j
			auto shadowPtr = AddComponent<Shadowmap>();
			//�e�̌`�i���b�V���j��ݒ�
			shadowPtr->SetMeshResource(L"DEFAULT_CUBE");
			if (m_bProjActive) {
				auto ptrDraw = AddComponent<PNTStaticDraw2>();
				ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
				ptrDraw->SetOwnShadowActive(true);
			}
			else {
				auto ptrDraw = AddComponent<PNTStaticDraw>();
				ptrDraw->SetMeshResource(L"DEFAULT_CUBE");
				ptrDraw->SetOwnShadowActive(true);
			}
		}

		//OBB�Փ˔����t����
		auto col = AddComponent<CollisionObb>();
		col->SetFixed(true);
		auto scene = App::GetApp()->GetScene<Scene>();
		if (scene->GetDebugState() == DebugState::Debug) {
			col->SetDrawActive(true);
		}
	}

	void Block::OnUpdate() {
		UpdateArt<CollisionObb>(OnGetDrawCamera(), GetComponent<CollisionObb>());
	}
}
//end basecross
