/*!
@file StaticPlatePolygon.h
@brief 雰囲気を出すための絵
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"

namespace basecross {
	class StaticPlatePolygon :public StageObject, public TrickArtBase {
		//テクスチャタグ
		wstring m_texName;
	public:
		StaticPlatePolygon(const shared_ptr<Stage>& stage,
			const wstring& line);
		StaticPlatePolygon(const shared_ptr<Stage>& stage,
			const wstring& texName, const ObjectParam& param);

		void OnCreate()override;
	};
}
//end basecross
