/*!
@file SpikesArt.h
@brief トリックアートの棘クラス
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"

namespace basecross {
	class SpikesArt :public StageObject {
		float m_artSize;
	public:
		SpikesArt(const shared_ptr<Stage>& stage,
			float artSize)
			:StageObject(stage),
			m_artSize(artSize)
		{}

		virtual void OnCreate()override;
	};

}
//end basecross
