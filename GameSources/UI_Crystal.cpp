#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void UI_Crystal::OnCreate()
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
		Vec3 pos(-640.0f, +325.0f, 0.0f);
		transComp->SetPosition(pos);
		transComp->SetScale(Vec3(0.75f));

		// ”š•”•ª‚Ì‰Šú‰»
		numbers.resize(2);
		Vec3 offset(120.0f, 0, 0);
		for (auto& number : numbers)
		{
			number = ObjectFactory::Create<Numbers>(GetStage(), 0);
			auto numberTrans = number->GetComponent<Transform>();
			numberTrans->SetPosition(pos + offset); // —×‚É•À‚Ô”š
			numberTrans->SetScale(Vec3(0.75f));
			offset += Vec3(35.0f, 0, 0); // ”š‚Ì•‚Ì•¶
		}
	}

	void UI_Crystal::OnUpdate()
	{
		for (auto& number : numbers)
		{
			auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
			int value = player->GetCrystal();
			number->SetValue(value); // ”š‚ğXV
		}
	}

	void UI_Crystal::OnDraw()
	{
		GameObject::OnDraw();
		for (auto& number : numbers) // ŠeŒ…‚Ì”š‚ğ•`‰æ‚·‚é
		{
			number->OnDraw();
		}
	}
}