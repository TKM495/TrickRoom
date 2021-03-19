#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Numbers::OnCreate()
	{
		float fNumber = static_cast<float>(number);
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		vertices = {
			{Vec3(0.0f,    0.0f,0.0f),color,Vec2((fNumber + 0) * 50.0f / 512.0f, 100.0f / 512.0f)},
			{Vec3(50.0f,   0.0f,0.0f),color,Vec2((fNumber + 1) * 50.0f / 512.0f, 100.0f / 512.0f)},
			{Vec3(0.0f, -100.0f,0.0f),color,Vec2((fNumber + 0) * 50.0f / 512.0f, 200.0f / 512.0f)},
			{Vec3(50.0f,-100.0f,0.0f),color,Vec2((fNumber + 1) * 50.0f / 512.0f, 200.0f / 512.0f)},
		};
		std::vector<uint16_t> indices = {
			0,1,2,
			2,1,3
		};
		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);
		drawComp->SetTextureResource(L"point");

		SetAlphaActive(true);

	}
}
