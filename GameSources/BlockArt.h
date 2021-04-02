/*!
@file BlockArt.h
@brief ブロックトリックアート
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class BlockArt :public TrickArtBase {
	public:
		BlockArt(const shared_ptr<Stage>& stage,
			const wstring& line);

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}
//end basecross
