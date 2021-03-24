/*!
@file BlockArt.h
@brief �u���b�N�g���b�N�A�[�g
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
