#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void Timer::OnCreate()
	{
		GetStage()->SetSharedGameObject(L"Timer", GetThis<Timer>());
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
		drawComp->SetTextureResource(L"timer");

		SetAlphaActive(true);

		auto transComp = AddComponent<Transform>();
		Vec3 pos(+350.0f, +400.0f, 0.0f);
		transComp->SetScale(0.5f, 0.5f, 0.5f);
		transComp->SetPosition(pos);

		// ���������̏�����
		numbers.resize(4);
		Vec3 offset(130.0f, -40.0f, 0.0f);
		for (auto& number : numbers)
		{
			number = ObjectFactory::Create<Numbers>(GetStage(), 0, Col4(1.0f));
			auto numberTrans = number->GetComponent<Transform>();
			numberTrans->SetPosition(pos + offset); // TIME�ׂ̗ɐ��������Ԃ悤�ɂ��炷
			numberTrans->SetScale(Vec3(0.75f));

			offset += Vec3(45.0f, 0.0f, 0.0f); // �����̕��̕���������ɂ��炷
		}
	}

	void Timer::OnUpdate()
	{
		auto& app = App::GetApp(); // �A�v���̎Q�Ǝ擾
		float delta = app->GetElapsedTime();
		auto camera = dynamic_pointer_cast<MainCamera>(OnGetDrawCamera());
		if (camera->GetbLeapFlg()) {
			return;
		}

		if (bup)count += delta; // 1�t���[��������̕b�������Z
		if (count > 1.0f && timer < pow(10, numbers.size()) - 1)
		{
			count = 0.0f; // ���b�J�E���g�����Z�b�g
			timer++;
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

	void Timer::Start()
	{
		bup = true;
	}

	void Timer::Stop()
	{
		bup = false;
	}

	float Timer::GetTime()
	{
		return timer;
	}

}