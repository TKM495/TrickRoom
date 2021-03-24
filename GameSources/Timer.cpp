#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void Timer::OnCreate()
	{
		float fontspace = 15.0f;
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		std::vector<VertexPositionColorTexture> vertices = {
			{Vec3(0.0f,    0.0f, 0.0f), color, Vec2(0.0f,            0.0f)},
			{Vec3(400.0f,    0.0f, 0.0f), color, Vec2(400.0f / 512.0f,            0.0f)},
			{Vec3(0.0f, -100.0f, 0.0f), color, Vec2(0.0f, 100.0f / 512.0f)},
			{Vec3(400.0f, -100.0f, 0.0f), color, Vec2(400.0f / 512.0f, 100.0f / 512.0f)}
		};
		std::vector<uint16_t> indices = {
			0, 1, 2,
			2, 1, 3
		};
		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);
		drawComp->SetTextureResource(L"time");

		SetAlphaActive(true);

		auto transComp = AddComponent<Transform>();
		Vec3 pos(380.0f, +400.0f, 0.0f);
		transComp->SetScale(0.5f, 0.5f, 0.5f);
		transComp->SetPosition(pos);

		// ���������̏�����
		numbers.resize(4);
		Vec3 offset(150.0f, 0.0f, 0.0f);
		for (auto& number : numbers)
		{
			number = ObjectFactory::Create<Numbers>(GetStage(), 0);
			auto numberTrans = number->GetComponent<Transform>();
			numberTrans->SetPosition(pos + offset); // TIME�ׂ̗ɐ��������Ԃ悤�ɂ��炷
			numberTrans->SetScale(0.5f, 0.5f, 0.5f);
			offset += Vec3(25.0f, 0.0f, 0.0f); // �����̕��̕���������ɂ��炷
		}
	}

	void Timer::OnUpdate()
	{
		auto& app = App::GetApp(); // �A�v���̎Q�Ǝ擾
		float delta = app->GetElapsedTime();

		count += delta; // 1�t���[��������̕b�������Z
		if (count > 1.0f && timer < pow(10, numbers.size()) - 1)
		{
			count = 0.0f; // ���b�J�E���g�����Z�b�g
			timer--;
		}

		if (timer <= 0) // ����0�b�ɂȂ�����
		{
			timer = 0; // 0�b�ɂȂ�����߂�
		}

		int place = static_cast<int>(pow(10, numbers.size() - 1));
		for (auto& number : numbers)
		{
			int value = timer / place % 10;
			place /= 10;

			number->SetValue(value); // �������X�V
		}

	}

	void Timer::OnDraw()
	{
		GameObject::OnDraw();
		for (auto& number : numbers)
		{
			number->OnDraw();
		}
	}
}