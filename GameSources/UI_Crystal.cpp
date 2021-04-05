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
		Vec3 pos(420.0f, +325.0f, 0.0f);
		transComp->SetPosition(pos);
		transComp->SetScale(Vec3(0.75f));

		// 数字部分の初期化
		numbers.resize(2);
		Vec3 offset(140.0f, -40.0f, 0);
		for (auto& number : numbers)
		{
			number = ObjectFactory::Create<Numbers>(GetStage(), 0, Col4(1.0f));
			auto numberTrans = number->GetComponent<Transform>();
			numberTrans->SetPosition(pos + offset); // 隣に並ぶ数字
			numberTrans->SetScale(Vec3(0.75f));
			offset += Vec3(45.0f, 0, 0); // 数字の幅の文
		}
	}

	void UI_Crystal::OnUpdate()
	{
		int place = static_cast<int>(pow(10, numbers.size() - 1));
		for (auto& number : numbers)
		{
			auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
			auto crystal = player->GetCrystal();
			int value = (crystal / place) % 10; //任意の桁を取り出す
			place /= 10;
			number->SetValue(value); // 数字を更新
		}
	}

	void UI_Crystal::OnDraw()
	{
		GameObject::OnDraw();
		for (auto& number : numbers) // 各桁の数字を描画する
		{
			number->OnDraw();
		}
	}
}