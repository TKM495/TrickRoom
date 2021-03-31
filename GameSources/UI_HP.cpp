#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void UI_HP::OnCreate()
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
		drawComp->SetTextureResource(L"heart");

		SetAlphaActive(true);

		auto transComp = AddComponent<Transform>();
		Vec3 pos(420.0f, +400.0f, 0.0f);
		transComp->SetPosition(pos);
		transComp->SetScale(Vec3(0.75f));

		// ���������̏�����
		numbers.resize(1);
		Vec3 offset(140.0f, -40.0f, 0);
		for (auto& number : numbers)
		{
			number = ObjectFactory::Create<Numbers>(GetStage(), 0); // �V�����I�u�W�F�N�g�𐶐�����B�������A�X�e�[�W�ɂ͒ǉ����Ȃ��B
			auto numberTrans = number->GetComponent<Transform>();
			numberTrans->SetPosition(pos + offset); // SCORE���x���ׂ̗ɕ��Ԑ���
			numberTrans->SetScale(Vec3(0.75f));
			offset += Vec3(45.0f, 0, 0); // �����̕��̕�
		}
	}

	void UI_HP::OnUpdate()
	{
		for (auto& number : numbers)
		{
			auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
			int value = player->GetHP();
			number->SetValue(value); // �������X�V
		}
	}

	void UI_HP::OnDraw()
	{
		GameObject::OnDraw();// (heart�̕������\�������j
		for (auto& number : numbers) // �e���̐�����`�悷��
		{
			number->OnDraw();
		}
	}
}