/*!
@file Scene.h
@brief �V�[��
*/
#pragma once

#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase{
		//�X�v���C�g�pCSV�f�[�^
		vector<wstring> m_spriteWData;
		//�I�u�W�F�N�g�pCSV�f�[�^
		vector<wstring> m_objectWData;

	public:
		Scene() :SceneBase(){}
		virtual ~Scene() {}
		virtual void OnCreate() override;
		virtual void OnEvent(const shared_ptr<Event>& event) override;

		vector<wstring>& GetSpriteData() {
			return m_spriteWData;
		}
		vector<wstring>& GetObjectData() {
			return m_objectWData;
		}
	};

}

//end basecross
