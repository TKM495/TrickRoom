/*!
@file Picture.h
@brief 雰囲気を出すための絵
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Picture :public StageObject {
		//テクスチャタグ
		wstring m_texName;
	public:
		Picture(const shared_ptr<Stage>& stage,
			const wstring& line);

		virtual void OnCreate()override;

	};
}
//end basecross
