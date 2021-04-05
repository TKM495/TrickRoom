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

	struct PictureDataFormat {
		wstring name;		//����(�^�O�݂����Ȃ�)
		Vec2 size;			//�T�C�Y
		wstring fileName;	//�t�@�C���̖��O(�g���q�܂߂�)
	};

	class CSVLoad :public GameObject{
		vector<SpriteDataFormat> m_spriteData;
		vector<ObjectDataFormat> m_objectData;
		vector<PictureDataFormat> m_pictureData;
	public:
		CSVLoad(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		virtual void OnCreate()override;

		void SpriteDataExtraction(vector<wstring> fileData);
		void ObjectDataExtraction(vector<wstring> fileData);
		void PictureDataExtraction(vector<wstring> fileData);

		vector<SpriteDataFormat>& GetSpriteData(){
			return m_spriteData;
		}

		vector<ObjectDataFormat>& GetObjectData(){
			return m_objectData;
		}

		vector<PictureDataFormat>& GetPictureData(){
			if (m_pictureData.size() == 0) {
				throw BaseException(
					L"�f�[�^�����݂��Ȃ��ɂ�������炸�A\n�擾���悤�Ƃ��܂����B",
					L"Size : " + to_wstring(m_pictureData.size()),
					L"CSVLoad::GetPictureData()"
				);
			}
			return m_pictureData;
		}
	};
}
//end basecross