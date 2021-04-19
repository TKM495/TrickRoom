#pragma once
#include "stdafx.h"
#include "MainCamera.h"
#include "AdvCollision.h"

namespace basecross {
	class TrickArtBase {
		Vec3 m_dirValue;
		int m_MAX;
		state m_dir;
	protected:
		//トリックアート投影フラグ
		bool m_bProjActive;
		//トリックアートとして描画するか
		bool m_tirckFlg;
		//トリックアートのときどの方向から見るか
		state m_activeState;
		//当たり判定のやつ
		vector<shared_ptr<AdvCollision>> m_myCols;

		//このクラスを継承したオブジェクトの方向ベクトルを取得
		Vec3 GetMyDirValue() {
			return m_dirValue;
		}
	public:
		//TADirectionの項目の数を返す(1～)
		int GetTypeNum() {
			return m_MAX;
		}
		//自身の方向をセット
		//(コンポーネントもこの関数を使うためpublic)
		void SetDir(state dir);
		//自身の方向を取得
		state GetDir() {
			return m_dir;
		}
		//特定の方向の方向ベクトルを取得
		static Vec3 GetDirValue(state dir);
		TrickArtBase();
	};
}
// end basecross