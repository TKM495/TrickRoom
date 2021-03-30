/*!
@file FloorGenerator.h
@brief è∞ê∂ê¨
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class FloorGenerator :public GameObject {
		int m_width;
		int m_height;
		Vec3 m_origin;
	public:
		FloorGenerator(const shared_ptr<Stage>& stage,
			const wstring& line);

		virtual void OnCreate()override;
	};

}
//end basecross
