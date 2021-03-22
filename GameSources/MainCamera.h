/*!
@file MainCamera.h
@brief ƒƒCƒ“ƒJƒƒ‰‚È‚Ç
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	enum class state
	{
		Right,
		Left
	};

	class MainCamera :public Camera
	{

		Vec3 m_offset;
		Vec3 m_Angle;
		bool bSetPers;
		float SetWidth;
		float SetHeight;
		Vec3 GetAngle();

		state m_CameraState;

	public:
		MainCamera();

		void OnCreate() override;
		void OnUpdate() override;

	};
}
