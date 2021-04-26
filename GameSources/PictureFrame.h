/*!
@file PictureFrame.h
@brief StageSelect‚ÅŽg‚¤‚â‚Â
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class PictureFrame :public StageObject {
		Vec2 m_frameSize;
	public:
		PictureFrame(const shared_ptr<Stage>& stage,
			const Vec2& frameSize=Vec2(560.0f))
			:StageObject(stage),
			m_frameSize(frameSize)
		{}

		void OnCreate()override;

		void SetPos(Vec2 pos);
		void SetSize(float size);
		Vec2 GetPos();
		float GetSize();
	};
}
//end basecross
