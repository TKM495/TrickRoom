/*!
@file Crystal.h
@brief ƒNƒŠƒXƒ^ƒ‹
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"

namespace basecross {
	class Crystal :public StageObject {
		Col4 m_color;
	public:
		Crystal(const shared_ptr<Stage>& stage,
			const wstring& line);

		virtual void OnCreate()override;
	};

}
//end basecross
