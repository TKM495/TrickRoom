/*!
@file CSVLoad.cpp
@brief
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void CSVLoad::OnCreate() {
		GetStage()->SetSharedGameObject(L"CSVLoad", GetThis<CSVLoad>());
	}

	void CSVLoad::SpriteDataExtraction(vector<wstring> fileData) {
		if (fileData.size() == 0) {
			throw BaseException(
				L"データがありません",
				L"Size : " + to_wstring(fileData.size()),
				L"CSVLoad::SpriteDataExtraction()"
			);
		}
		//0番目(1行目は見出しなので除外)
		for (size_t i = 1; i < fileData.size(); i++) {
			//トークン（カラム）の配列
			vector<wstring> tokens;

			//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(tokens, fileData[i], L',');

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

	void CSVLoad::ObjectDataExtraction(vector<wstring> fileData) {
		if (fileData.size() == 0) {
			throw BaseException(
				L"データがありません",
				L"Size : " + to_wstring(fileData.size()),
				L"CSVLoad::ObjectDataExtraction()"
			);
		}
		//0番目(1行目は見出しなので除外)
		for (size_t i = 1; i < fileData.size(); i++) {
			//トークン（カラム）の配列
			vector<wstring> tokens;

			//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(tokens, fileData[i], L',');

			ObjectDataFormat data;
			data.name = tokens[0];
			data.position = Vec3(
				(float)_wtof(tokens[1].c_str()),
				(float)_wtof(tokens[2].c_str()),
				(float)_wtof(tokens[3].c_str())
			);
			data.scale = Vec3(
				(float)_wtof(tokens[4].c_str()),
				(float)_wtof(tokens[5].c_str()),
				(float)_wtof(tokens[6].c_str())
			);
			data.rotation = Vec3(
				(float)_wtof(tokens[7].c_str()),
				(float)_wtof(tokens[8].c_str()),
				(float)_wtof(tokens[9].c_str())
			);

			m_objectData.push_back(data);
		}
	}

	void CSVLoad::PictureDataExtraction(vector<wstring> fileData) {
		if (fileData.size() == 0) {
			//画像は必須ではないのでエラーは出さない
			return;
		}
		//0番目(1行目は見出しなので除外)
		for (size_t i = 1; i < fileData.size(); i++) {
			//トークン（カラム）の配列
			vector<wstring> tokens;

			//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(tokens, fileData[i], L',');

			PictureDataFormat data;
			data.name = tokens[0];
			data.size = Vec2(
				(float)_wtof(tokens[1].c_str()),
				(float)_wtof(tokens[2].c_str())
			);

			data.fileName = tokens[3];

			m_pictureData.push_back(data);
		}
	}
}
//end basecross