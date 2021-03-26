/*!
@file FloorArt.h
@brief 床のトリックアート
*/

#pragma once
#include "stdafx.h"
#include "TrickArtBase.h"
#include "MainCamera.h"

namespace basecross {
	class FloorArt :public TrickArtBase {
		state m_activeState;
	public:
		FloorArt(const shared_ptr<Stage>& stage,
			const wstring& line);

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};


}
//end basecross
