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
		Left,
		moveflg
	};

	class MainCamera :public Camera
	{

		Vec3 m_offset;
		Vec3 m_Angle;
		bool bSetPers;
		float SetWidth;
		float SetHeight;
		Vec3 GetAngle();
		bool bLeapFlg;
		float m_LeapTime;
		float m_LeapSpeed;
		Vec3 m_Eye;
		Vec3 m_LeapOffset;

		state m_CameraState;

		bool isFirst;

	public:
		MainCamera();

		void OnCreate() override;
		void OnUpdate() override;

		bool GetbLeapFlg();
	};
}
