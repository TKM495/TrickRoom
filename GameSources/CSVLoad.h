/*!
@file CSVLoad.h
@brief
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//�X�v���C�g�̃f�[�^�`��
	struct SpriteDataFormat
	{
		wstring name;	//����
		Vec2 origin;	//���_�̍��W
		Vec2 size;		//�T�C�Y
	};

	class CSVLoad :public GameObject{
		vector<SpriteDataFormat> m_spriteData;
		vector<wstring>& m_spriteFileData;
	public:
		CSVLoad(const shared_ptr<Stage>& stage,
			vector<wstring>& fileData)
			:GameObject(stage),
			m_spriteFileData(fileData)
		{}

		virtual void OnCreate()override;

		vector<SpriteDataFormat>& GetSpriteData(){
			return m_spriteData;
		}
	};
}
//end basecross