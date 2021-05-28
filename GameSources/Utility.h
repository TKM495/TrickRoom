/*!
@file Utility.h
@brief �����Ȋ֐�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	namespace Utility{
		//�f�[�^�̒�����l�[���Ɉ�v����C���f�b�N�X��Ԃ��֐�
		template<class T>
		int SearchDataIndex(vector<T>& data, wstring name) {
			for (int i = 0; i < data.size(); i++) {
				if (data[i].name == name) {
					return i;
				}
			}
			//�����ɗ����炻�̃f�[�^�͑��݂��Ȃ�
			return -1;
		}
		//�z��̃T�C�Y��Ԃ��֐�
		template<typename TYPE,size_t SIZE>
		size_t GetArrayLength(const TYPE(&)[SIZE])
		{
			return SIZE;
		}
		//�e�N�X�`���̃T�C�Y��Ԃ��֐�
		const Vec2 GetTextureSize(const wstring& key);
		//�e�N�X�`���̍��W��UV���W�ɕϊ�����֐�(1�Z�b�g)
		const Vec2 ConvertToUVCoordinate(const Vec2& coordinate, const Vec2& textureSize);
		const Vec2 ConvertToUVCoordinate(const Vec2& coordinate, const wstring& textureName);
		//�e�N�X�`���̍��W��UV���W�ɕϊ�����֐�(����)
		void ConvertToUVCoordinates(const vector<Vec2>& coordinates, const Vec2& textureSize, vector<Vec2>& uv);
		void ConvertToUVCoordinates(const vector<Vec2>& coordinates, const wstring& textureName, vector<Vec2>& uv);
		//Vec3��deg��rad�ɕϊ�
		Vec3 ConvertDegVecToRadVec(const Vec3& deg);
		Vec3 ConvertRadVecToDegVec(const Vec3& rad);

		//2�̊p�x(deg)���������ǂ����𒲂ׂ�(true:������,false:�قȂ�)
		bool MatchAngle(float deg1, float deg2);
		//�p�x(deg)��min�`max�̊ԂɎ��߂�
		//(min��max�̍���360�ł���K�v������)
		float ClampAngle(float min, float max, float angle);
		//wstring��bool�ɕϊ�
		bool WStrToBool(wstring str);

		//Col4��0�`255��0�`1�Ɏ��߂�
		Col4 ConvertColorZeroToOne(Col4 color);
	}
}
//end basecross
