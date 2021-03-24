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

	struct ObjectDataFormat {
		wstring name;	//����
		Vec3 position;	//�ʒu
		Vec3 scale;		//�傫��
		Vec3 rotation;	//��]
	};

	class CSVLoad :public GameObject{
		vector<SpriteDataFormat> m_spriteData;
		vector<ObjectDataFormat> m_objectData;
		vector<wstring>& m_fileData;
	public:
		CSVLoad(const shared_ptr<Stage>& stage,
			vector<wstring>& fileData)
			:GameObject(stage),
			m_fileData(fileData)
		{}

		void SpriteDataExtraction();
		void ObjectDataExtraction();

		vector<SpriteDataFormat>& GetSpriteData(){
			return m_spriteData;
		}

		vector<ObjectDataFormat>& GetObjectData(){
			return m_objectData;
		}
	};
}
//end basecross