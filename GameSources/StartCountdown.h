/*!
@file StartCountdown.h
@brief スタート時のカウントダウン演出
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class StartCountdown :public GameObject {
		//数字オブジェクト
		shared_ptr<Numbers> m_numObjs[3];
		//文字オブジェクト
		shared_ptr<StringSprite2> m_strObj;
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

	};

}
//end basecross
