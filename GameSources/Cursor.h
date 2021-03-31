/*!
@file Cursor.h
@brief メニュー用のカーソルクラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Cursor :public GameObject {
	public:
		Cursor(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		virtual void OnCreate()override;
	};

}
//end basecross
