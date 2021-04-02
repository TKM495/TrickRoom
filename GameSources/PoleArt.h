/*!
@file PoleArt.h
@brief ポールのトリックアート
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PoleArt :public TrickArtBase {
	public:
		PoleArt(const shared_ptr<Stage>& stage,
			const wstring& line);

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}
//end basecross
