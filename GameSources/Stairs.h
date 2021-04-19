/*!
@file Stairs.h
@brief ŠK’i
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Stairs :public StageObject ,public TrickArtBase{
	public:
		Stairs(const shared_ptr<Stage>& stage,
			const wstring& line);

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}
//end basecross
