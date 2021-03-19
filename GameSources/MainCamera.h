/*!
@file MainCamera.h
@brief ƒƒCƒ“ƒJƒƒ‰‚È‚Ç
*/

#pragma once
#include "stdafx.h"
#include "InputHandler.h"

namespace basecross {
	class MainCamera :public Camera
	{
		InputHandler<MainCamera> m_InputHandler;

		Vec3 m_offset;
		Vec3 m_Angle;
		bool bSetPers;
		float m_width;
		float m_height;
		Vec3 GetAngle();

	public:
		MainCamera();

		void OnCreate() override;
		void OnUpdate() override;

		void OnPushA();
		void OnPushB();
		void OnPushX() {}
		void OnPushY() {}
		void OnPushStart(){}
		void OnPushBack() {}

	};
}
