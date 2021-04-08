/*!
@file CSVLoad.h
@brief
*/

#pragma once
#include "stdafx.h"
#include "SpriteManager.h"

namespace basecross {
	//�X�v���C�g�̃f�[�^�`��
	struct SpriteDataFormat {
		wstring name;	//����
		Vec2 origin;	//���_�̍��W
		Vec2 size;		//�T�C�Y
	};

	struct PictureDataFormat {
		wstring name;		//����(�^�O�݂����Ȃ�)
		Vec2 size;			//�T�C�Y
		wstring fileName;	//�t�@�C���̖��O(�g���q�܂߂�)
	};

	enum class SpriteType {
		String,
		Image,
		Number
	};

	class CSVLoad :public GameObject{
		vector<SpriteDataFormat> m_stringSpriteData;
		vector<SpriteDataFormat> m_imageSpriteData;
		vector<PictureDataFormat> m_pictureData;
	public:
		CSVLoad(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		virtual void OnCreate()override;

		void SpriteDataExtraction(vector<wstring> fileData, SpriteType type);
		void PictureDataExtraction(vector<wstring> fileData);

		vector<SpriteDataFormat>& GetStringSpriteData(){
			return m_stringSpriteData;
		}

		vector<SpriteDataFormat>& GetImageSpriteData(){
			return m_imageSpriteData;
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