/*!
@file BGSprite.h
@brief �w�i�p�X�v���C�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class BGSprite :public GameObject {
		//�e�N�X�`���l�[��
		wstring m_texName;
	public:
		BGSprite(const shared_ptr<Stage>& stage,
			const wstring& name = L"")
			:GameObject(stage),
			m_texName(name)
		{}

		virtual void OnCreate()override;
		void SetPosition(Vec3 pos) {
			GetComponent<Transform>()->SetPosition(pos);
		}
	};
}
//end basecross
