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
	}
}
//end basecross
