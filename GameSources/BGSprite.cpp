/*!
@file BGSprite.cpp
@brief 背景用スプライト実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void BGSprite::OnCreate() {
		auto viewport = GetStage()->GetView()->GetTargetViewport();

		auto halfWidth = viewport.Width / 2.0f;
		auto halfHeight = viewport.Height / 2.0f;

		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		std::vector<VertexPositionColorTexture> vertices = {
			{Vec3(-halfWidth, +halfHeight, 0.0f), color, Vec2(0.0f,0.0f)},
			{Vec3(+halfWidth, +halfHeight, 0.0f), color, Vec2(1.0f,0.0f)},
			{Vec3(-halfWidth, -halfHeight, 0.0f), color, Vec2(0.0f,1.0f)},
			{Vec3(+halfWidth, -halfHeight, 0.0f), color, Vec2(1.0f,1.0f)}
		};
		std::vector<uint16_t> indices = {
			0, 1, 2,
			2, 1, 3
		};
		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);
		if (m_texName != L"") {
			drawComp->SetTextureResource(m_texName);
		}

		//背景は最も後ろにあるべきものなので数を(-方向に)大きくしている
		SetDrawLayer(-5);
	}
}
//end basecross
