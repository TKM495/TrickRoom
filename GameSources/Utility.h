/*!
@file Utility.h
@brief いろんな関数
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	namespace Utility{
		//データの中からネームに一致するインデックスを返す関数
		template<class T>
		int SearchDataIndex(vector<T>& data, wstring name) {
			for (int i = 0; i < data.size(); i++) {
				if (data[i].name == name) {
					return i;
				}
			}
			//ここに来たらそのデータは存在しない
			return -1;
		}
	}
}
//end basecross
