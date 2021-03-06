/*!
@file FallingArea.h
@brief 落下判定エリア
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"

namespace basecross {
	class FallingArea :public StageObject {
		bool m_bProjActive;
	public:
		FallingArea(const shared_ptr<Stage>& stage,
			const wstring& line);

		void OnCreate()override;
	};
}
//edn basecross