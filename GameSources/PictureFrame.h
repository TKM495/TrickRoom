/*!
@file PictureFrame.h
@brief StageSelect‚ÅŽg‚¤‚â‚Â
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PictureFrame :public StageObject {
	public:
		PictureFrame(const shared_ptr<Stage>& stage)
			:StageObject(stage)
		{}

		void OnCreate()override;

		void SetPos(Vec2 pos);
		void SetSize(float size);
		Vec2 GetPos();
		float GetSize();
	};
}
//end basecross
