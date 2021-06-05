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
				L"�f�[�^������܂���",
				L"Size : " + to_wstring(fileData.size()),
				L"CSVLoad::SpriteDataExtraction()"
			);
		}
		//0�Ԗ�(1�s�ڂ͌��o���Ȃ̂ŏ��O)
		for (size_t i = 1; i < fileData.size(); i++) {
			//�g�[�N���i�J�����j�̔z��
			vector<wstring> tokens;

			//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
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
				break;
			case SpriteType::Number:
				break;
			default:
				break;
			}
		}
	}
}
//end basecross