#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Crystal::OnCreate()
	{
		Col4 color(1.0f, 1.0f, 1.0f, 0.5f);
		std::vector<VertexPositionColorTexture> vertices = {
			{Vec3(0.0f,    0.0f, 0.0f), color, Vec2(0.0f,0.0f)},
			{Vec3(400.0f,    0.0f, 0.0f), color, Vec2(400.0f / 512.0f,0.0f)},
			{Vec3(0.0f, -100.0f, 0.0f), color, Vec2(0.0f, 100.f / 512.0f)},
			{Vec3(400.0f, -100.0f, 0.0f), color, Vec2(400.0f / 512.0f, 100.f / 512.0f)}
		};
		std::vector<uint16_t> indices = {
			0, 1, 2,
			2, 1, 3
		};
		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);
		drawComp->SetTextureResource(L"crystal");

		SetAlphaActive(true);

		auto transComp = AddComponent<Transform>();
		Vec3 pos(-640.0f, +250.0f, 0.0f);
		transComp->SetPosition(pos);

		// ”š•”•ª‚Ì‰Šú‰»
		numbers.resize(1);
		Vec3 offset(150.0f, 0, 0);
		for (auto& number : numbers)
		{
			number = ObjectFactory::Create<Numbers>(GetStage(), 0);
			auto numberTrans = number->GetComponent<Transform>();
			numberTrans->SetPosition(pos + offset); // —×‚É•À‚Ô”š
			offset += Vec3(50.0f, 0, 0); // ”š‚Ì•‚Ì•¶
		}
	}

	void Crystal::OnUpdate()
	{
	}

	void Crystal::OnDraw()
	{
		GameObject::OnDraw();
		for (auto& number : numbers) // ŠeŒ…‚Ì”š‚ğ•`‰æ‚·‚é
		{
			number->OnDraw();
		}
	}
}