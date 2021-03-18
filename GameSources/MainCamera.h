/*!
@file MainCamera.h
@brief ƒƒCƒ“ƒJƒƒ‰‚È‚Ç
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MainCamera :public Camera
	{

		Vec3 m_offset;

	public:
		MainCamera();

		void OnCreate() override;
		void OnUpdate() override;

	};
}
