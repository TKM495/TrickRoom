#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Score::OnCreate()
	{
		Col4 color(1.0f, 1.0f, 1.0f, 0.5f);
		std::vector<VertexPositionColorTexture> vertices = {
			{Vec3(0.0f,    0.0f, 0.0f), color, Vec2(0.0f,           0.0f)},
			{Vec3(400.0f,    0.0f, 0.0f), color, Vec2(400.0f / 512.0f,           0.0f)},
			{Vec3(0.0f, -100.0f, 0.0f), color, Vec2(0.0f, 100.f / 512.0f)},
			{Vec3(400.0f, -100.0f, 0.0f), color, Vec2(400.0f / 512.0f, 100.f / 512.0f)}
		};
		std::vector<uint16_t> indices = {
			0, 1, 2,
			2, 1, 3
		};
		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);
		drawComp->SetTextureResource(L"point");

		SetAlphaActive(true);

		auto transComp = AddComponent<Transform>();
		Vec3 pos(-300.0f, +400.0f, 0.0f);
		transComp->SetPosition(pos);

		// 数字部分の初期化
		numbers.resize(5);
		Vec3 offset(300.0f, 0, 0);
		for (auto& number : numbers)
		{
			number = ObjectFactory::Create<Numbers>(GetStage(), 0); // 新しいオブジェクトを生成する。ただし、ステージには追加しない。
			auto numberTrans = number->GetComponent<Transform>();
			numberTrans->SetPosition(pos + offset); // SCOREラベルの隣に並ぶ数字
			offset += Vec3(50.0f, 0, 0); // 数字の幅の文
		}

		int place = static_cast<int>(pow(10, numbers.size() - 1)); // 10の累乗を使って、桁(位)を求める
		for (auto& number : numbers)
		{
			int value = score / place % 10; // 対象の桁を切り出す
			place /= 10; // 桁(位)を下げる

			number->SetValue(value); // 数字を更新する
		}
	}

	//void Score::OnUpdate()
	//{

	//}

	void Score::OnDraw()
	{
		GameObject::OnDraw();// (SCOREの文字が表示される）
		for (auto& number : numbers) // 各桁の数字を描画する
		{
			number->OnDraw();
		}
	}
}