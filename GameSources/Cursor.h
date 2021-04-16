/*!
@file Cursor.h
@brief メニュー用のカーソルクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Cursor :public GameObject {
		//色
		Col4 m_color;
		//最大透過率
		float m_max;
		//最小透過率
		float m_min;
		//速度
		float m_rate;
		//時間計測用
		float m_delta;
	public:
		Cursor(const shared_ptr<Stage>& stage)
			:GameObject(stage),
			m_max(0.3f), m_min(0.2f), m_rate(6.0f), m_delta(0.0f)
		{}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}
//end basecross
