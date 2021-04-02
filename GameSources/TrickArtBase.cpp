/*!
@file TrickArtBase.cpp
@brief �g���b�N�A�[�g�̊��N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TrickArtBase::OnCreate() {

		auto drawComp = AddComponent<PCTStaticDraw>();
		//���_�f�[�^�ƒ��_�C���f�b�N�X�����ƂɃ��b�V��(�|���S��)�𐶐�����
		drawComp->CreateOriginalMesh(m_vertices, m_indices);
		//���삵�����b�V�����g�p����
		drawComp->SetOriginalMeshUse(true);

		drawComp->SetSamplerState(SamplerState::AnisotropicWrap); //�e�N�X�`���̌J��Ԃ��ݒ�(Wrap)
		drawComp->SetDepthStencilState(DepthStencilState::Read);
		drawComp->SetTextureResource(m_texStr);

		SetAlphaActive(true); //�������T�|�[�g����&���ʕ`��ɂȂ�

		StageObject::OnCreate();
	}

	void TrickArtBase::OnUpdate() {

	}
}
//end basecross
