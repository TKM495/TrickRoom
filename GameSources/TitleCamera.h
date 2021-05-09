#pragma once
#include "stdafx.h"

namespace basecross {
	class TitleCamera : public Camera
	{
	protected:
		float m_angleRadX;
		float m_angleRadY;

		float m_Center;
		float m_XMax;
		float m_XMin;
		float m_YMax;
		float m_YMin;

		float length; // ƒJƒƒ‰‚Ì’‹“_‚©‚ç‚Ì‹——£

	public:
		TitleCamera()
			: m_angleRadX(XMConvertToRadians(-90)), length(10.0f),m_angleRadY(XMConvertToRadians(-90)),m_Center(90.0f),m_XMax(-120),m_XMin(-60),m_YMax(-120),m_YMin(-60)
		{
		}

		void OnCreate() override;
		void OnUpdate() override;

		float GetAngleRadY() const
		{
			return m_angleRadY;
		}
	};
}