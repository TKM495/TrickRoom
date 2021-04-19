#pragma once
#include "stdafx.h"

namespace basecross {
	// トリックアートの方向の定義
	enum class TADirection {
		Right,
		Left,
		MAX		//MAXは常に最後
	};

	class TrickArtBase {
		Vec3 m_dirValue;
		TADirection m_dir;
	protected:
		Vec3 GetMyDirValue() {
			return m_dirValue;
		}
	public:
		//TADirectionの項目の数を返す(1～)
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