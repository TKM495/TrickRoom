#pragma once
#include "stdafx.h"

namespace basecross {
	// �g���b�N�A�[�g�̕����̒�`
	enum class TADirection {
		Right,
		Left,
		MAX		//MAX�͏�ɍŌ�
	};

	class TrickArtBase {
		Vec3 m_dirValue;
		TADirection m_dir;
	protected:
		Vec3 GetMyDirValue() {
			return m_dirValue;
		}
	public:
		//TADirection�̍��ڂ̐���Ԃ�(1�`)
		int GetTypeNum() {
			return (int)TADirection::MAX;
		}
		void SetDir(TADirection dir);
		TADirection GetDir() {
			return m_dir;
		}
		static Vec3 GetDirValue(TADirection dir);
		TrickArtBase();
	};
}
// end basecross