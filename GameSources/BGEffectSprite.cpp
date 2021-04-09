/*!
@file BGSprite.cpp
@brief ”wŒi—pƒXƒvƒ‰ƒCƒgÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void BGEffectSprite::OnCreate() {
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
		else {
			drawComp->SetDiffuse(m_color);
		}
		SetAlphaActive(true);
		//”wŒi‚ÍÅ‚àŒã‚ë‚É‚ ‚é‚×‚«‚à‚Ì‚È‚Ì‚Å”‚ğ(-•ûŒü‚É)‘å‚«‚­‚µ‚Ä‚¢‚é
		SetDrawLayer(-4);
	}
}
//end basecross
