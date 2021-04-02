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

	class CSVLoad :public GameObject{
		vector<SpriteDataFormat> m_spriteData;
		vector<ObjectDataFormat> m_objectData;
	public:
		CSVLoad(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		virtual void OnCreate()override;

		void SpriteDataExtraction(vector<wstring> fileData);
		void ObjectDataExtraction(vector<wstring> fileData);

		vector<SpriteDataFormat>& GetSpriteData(){
			return m_spriteData;
		}

		vector<ObjectDataFormat>& GetObjectData(){
			return m_objectData;
		}
	};
}
//end basecross