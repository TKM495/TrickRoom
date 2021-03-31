/*!
@file CSVLoad.h
@brief
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//スプライトのデータ形式
	struct SpriteDataFormat
	{
		wstring name;	//名称
		Vec2 origin;	//原点の座標
		Vec2 size;		//サイズ
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