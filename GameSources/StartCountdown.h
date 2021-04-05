/*!
@file StartCountdown.h
@brief スタート時のカウントダウン演出
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class StartCountdown :public GameObject {
		//ゲームオブジェクト配列(4なのは1～3とスタート)
		shared_ptr<GameObject> m_objs[4];
		//時間計測用
		float m_delta;
		//ひとつ前の値
		int m_beforeValue;
		//Update()のなかで関数を一回だけ実行するためのフラグ
		bool m_bOneTime;
	public:
		StartCountdown(const shared_ptr<Stage>& stage)
			:GameObject(stage),
			m_delta(4.0f),
			m_bOneTime(false)
		{}

		void OnCreate()override;
		void OnUpdate()override;

		//カウントスタート
		void Start() {
			SetUpdateActive(true);
		}
	};

}
//end basecross
