/*!
@file CSVLoad.cpp
@brief
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void CSVLoad::OnCreate() {
		//0番目(1行目は見出しなので除外)
		for (size_t i = 1; i < m_spriteFileData.size(); i++) {
			//トークン（カラム）の配列
			vector<wstring> tokens;

			//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(tokens, m_spriteFileData[i], L',');

			SpriteDataFormat data;
			data.name = tokens[0];
			data.origin = Vec2(
				(float)_wtof(tokens[1].c_str()),
				(float)_wtof(tokens[2].c_str())
			);
			data.size = Vec2(
				(float)_wtof(tokens[3].c_str()),
				(float)_wtof(tokens[4].c_str())
			);

			m_spriteData.push_back(data);
		}
	}
}
//end basecross