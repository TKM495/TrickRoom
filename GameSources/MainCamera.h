/*!
@file MainCamera.h
@brief
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
		Vec3 m_CameraOffset;

		state m_CameraState;

		bool isFirst;
		void Zoom(float speed);
	public:
		MainCamera();

		void OnCreate() override;
		void OnUpdate() override;
		state GetCamState() {
			return m_CameraState;
		}

		bool GetbLeapFlg();
	};
}
