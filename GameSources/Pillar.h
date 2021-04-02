/*!
@file Pillar.h
@brief •µˆÍ‹C‚ğo‚·‚½‚ß‚Ì’Œ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Pillar :public StageObject {
	public:
		Pillar(const shared_ptr<Stage>& stage,
			const wstring& line);

		virtual void OnCreate()override;
	};

}
//end basecross
