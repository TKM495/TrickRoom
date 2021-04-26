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

	void CSVLoad::SpriteDataExtraction(vector<wstring> fileData, SpriteType type) {
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

			switch (type)
			{
			case SpriteType::String:
				m_stringSpriteData.push_back(data);
				break;
			case SpriteType::Image:
				m_imageSpriteData.push_back(data);
				break;
			case SpriteType::Number:
				break;
			default:
				break;
			}
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

	void CSVLoad::StageScoreDataExtraction(vector<wstring> fileData) {
		if (fileData.size() == 0) {
			throw BaseException(
				L"データがありません",
				L"Size : " + to_wstring(fileData.size()),
				L"CSVLoad::StageScoreDataExtraction()"
			);
		}
		//0番目(1行目は見出しなので除外)
		for (size_t i = 1; i < fileData.size(); i++) {
			//トークン（カラム）の配列
			vector<wstring> tokens;

			//トークン（カラム）単位で文字列を抽出(L','をデリミタとして区分け)
			Util::WStrToTokenVector(tokens, fileData[i], L',');

			StageScoreDataFormat data;
			data.StageNum = i + 1;
			for (int j = 0; j < (int)Rank::MAX; j++) {
				data.Time[j] = (float)_wtof(tokens[j + 1].c_str());
				data.CamNum[j] = (int)_wtof(tokens[j + 5].c_str());
			}
			m_stageScoreData.push_back(data);
		}
	}

}
//end basecross