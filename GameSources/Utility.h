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
		//配列のサイズを返す関数
		template<typename TYPE,size_t SIZE>
		size_t GetArrayLength(const TYPE(&)[SIZE])
		{
			return SIZE;
		}
		//テクスチャのサイズを返す関数
		const Vec2 GetTextureSize(const wstring& key);
		//テクスチャの座標をUV座標に変換する関数(1セット)
		const Vec2 ConvertToUVCoordinate(const Vec2& coordinate, const Vec2& textureSize);
		const Vec2 ConvertToUVCoordinate(const Vec2& coordinate, const wstring& textureName);
		//テクスチャの座標をUV座標に変換する関数(複数)
		void ConvertToUVCoordinates(const vector<Vec2>& coordinates, const Vec2& textureSize, vector<Vec2>& uv);
		void ConvertToUVCoordinates(const vector<Vec2>& coordinates, const wstring& textureName, vector<Vec2>& uv);
	}
}
//end basecross
