/*!
@file Plane.h
@brief 板オブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Plane :public StageObject {
	public:
		Plane(shared_ptr<Stage>& stage,
			const wstring& line);

		virtual void OnCreate()override;
	};
}
//end basecross
