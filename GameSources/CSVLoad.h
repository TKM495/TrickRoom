/*!
@file CSVLoad.h
@brief
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//スプライトのデータ形式
	struct SpriteDataFormat {
		wstring name;	//名称
		Vec2 origin;	//原点の座標
		Vec2 size;		//サイズ
	};

	struct ObjectDataFormat {
		wstring name;	//名称
		Vec3 position;	//位置
		Vec3 scale;		//大きさ
		Vec3 rotation;	//回転
	};

	struct PictureDataFormat {
		wstring name;		//名称(タグみたいなの)
		Vec2 size;			//サイズ
		wstring fileName;	//ファイルの名前(拡張子含める)
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
					L"データが存在しないにもかかわらず、\n取得しようとしました。",
					L"Size : " + to_wstring(m_pictureData.size()),
					L"CSVLoad::GetPictureData()"
				);
			}
			return m_pictureData;
		}
	};
}
//end basecross