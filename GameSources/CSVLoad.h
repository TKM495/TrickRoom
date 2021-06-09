/*!
@file CSVLoad.h
@brief
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//�X�v���C�g�̃f�[�^�`��
	struct SpriteDataFormat {
		wstring name;	//����
		Vec2 origin;	//���_�̍��W
		Vec2 size;		//�T�C�Y
	};

	enum class SpriteType {
		String,
		Image,
		Number
	};

	class CSVLoad :public GameObject{
		vector<SpriteDataFormat> m_stringSpriteData;
	public:
		CSVLoad(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		virtual void OnCreate()override;

		void SpriteDataExtraction(vector<wstring> fileData, SpriteType type);

		vector<SpriteDataFormat>& GetStringSpriteData(){
			return m_stringSpriteData;
		}
	};
}
//end basecross