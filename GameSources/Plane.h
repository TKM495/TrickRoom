/*!
@file Plane.h
@brief 板オブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Plane :public StageObject {
	public:
		Plane(shared_ptr<Stage>& stage,
			const Vec3& position,
			const Vec3& scale)
			:StageObject(stage)
		{
			m_position = position;
			m_scale = scale;
		}

		virtual void OnCreate()override;
	};

}
//end basecross
