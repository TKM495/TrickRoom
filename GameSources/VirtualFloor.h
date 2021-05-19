/*!
@file VirtualFloor.h
@brief 仮想床(テクスチャが貼れないオブジェクトに貼る用)クラス
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"

namespace basecross {
	class VirtualFloor :public StageObject, public TrickArtBase {
	public:
		VirtualFloor(const shared_ptr<Stage>& stage,
			const wstring& line);

		void OnCreate()override;
	};
}
//end basecross