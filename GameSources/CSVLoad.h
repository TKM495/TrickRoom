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