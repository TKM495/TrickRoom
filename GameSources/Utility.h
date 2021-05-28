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
		//Vec3のdegをradに変換
		Vec3 ConvertDegVecToRadVec(const Vec3& deg);
		Vec3 ConvertRadVecToDegVec(const Vec3& rad);

		//2つの角度(deg)が同じかどうかを調べる(true:等しい,false:異なる)
		bool MatchAngle(float deg1, float deg2);
		//角度(deg)をmin～maxの間に収める
		//(minとmaxの差は360である必要がある)
		float ClampAngle(float min, float max, float angle);
		//wstringをboolに変換
		bool WStrToBool(wstring str);

		//Col4の0～255を0～1に収める
		Col4 ConvertColorZeroToOne(Col4 color);
	}
}
//end basecross
