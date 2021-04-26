/*!
@file CSVLoad.h
@brief
*/

#pragma once
#include "stdafx.h"
#include "UI_Rank.h"

namespace basecross {
	//スプライトのデータ形式
	struct SpriteDataFormat {
		wstring name;	//名称
		Vec2 origin;	//原点の座標
		Vec2 size;		//サイズ
	};

	struct PictureDataFormat {
		wstring name;		//名称(タグみたいなの)
		Vec2 size;			//サイズ
		wstring fileName;	//ファイルの名前(拡張子含める)
	};

	enum class SpriteType {
		String,
		Image,
		Number
	};

	struct StageScoreDataFormat {
		int StageNum;
		float Time[(int)Rank::MAX];	//0～Rank::MAX(S～C)
		int CamNum[(int)Rank::MAX];
	};

	class CSVLoad :public GameObject{
		vector<SpriteDataFormat> m_stringSpriteData;
		vector<SpriteDataFormat> m_imageSpriteData;
		vector<PictureDataFormat> m_pictureData;
		vector<StageScoreDataFormat> m_stageScoreData;
	public:
		CSVLoad(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		virtual void OnCreate()override;

		void SpriteDataExtraction(vector<wstring> fileData, SpriteType type);
		void PictureDataExtraction(vector<wstring> fileData);
		void StageScoreDataExtraction(vector<wstring> fileData);

		vector<SpriteDataFormat>& GetStringSpriteData(){
			return m_stringSpriteData;
		}

		vector<SpriteDataFormat>& GetImageSpriteData(){
			return m_imageSpriteData;
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

		vector<StageScoreDataFormat>& GetStageScoreData() {
			return m_stageScoreData;
		}
	};
}
//end basecross