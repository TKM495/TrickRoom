/*!
@file illusionFrame.h
@brief ö‹ƒtƒŒ[ƒ€
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class illusionFrame :public GameObject {
	public:
		enum class Status {
			Active,
			Invalid,
			Neutral
		};
	private:
		bool m_bItemActive;
		wstring m_texName;
		vector<VertexPositionColorTexture> vertices;
	public:
		illusionFrame(const shared_ptr<Stage>& stage,
			const wstring& texName)
			:GameObject(stage), m_bItemActive(false), m_texName(texName)
		{}

		void OnCreate()override;
		void SetPosition(Vec2 pos);
		void SetFrameActive(Status stat);
	};
}
//end basecross