/*!
@file StairsArt.h
@brief 階段のトリックアート
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"
#include "MainCamera.h"

namespace basecross {
	class StairsArt :public TrickArtBaseOld {
		state m_activeState;
	public:
		StairsArt(const shared_ptr<Stage>& stage,
			const wstring& line);

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}
//end basecross
