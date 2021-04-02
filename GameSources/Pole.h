/*!
@file Pole.h
@brief É|Å[Éã
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Pole :public StageObject {
	public:
		Pole(const shared_ptr<Stage>& stage,
			const wstring& line);

		virtual void OnCreate()override;
	};

}
//end basecross
