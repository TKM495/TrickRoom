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

		// ���������̏�����
		numbers.resize(5);
		Vec3 offset(300.0f, 0, 0);
		for (auto& number : numbers)
		{
			number = ObjectFactory::Create<Numbers>(GetStage(), 0); // �V�����I�u�W�F�N�g�𐶐�����B�������A�X�e�[�W�ɂ͒ǉ����Ȃ��B
			auto numberTrans = number->GetComponent<Transform>();
			numberTrans->SetPosition(pos + offset); // SCORE���x���ׂ̗ɕ��Ԑ���
			offset += Vec3(50.0f, 0, 0); // �����̕��̕�
		}

		int place = static_cast<int>(pow(10, numbers.size() - 1)); // 10�̗ݏ���g���āA��(��)�����߂�
		for (auto& number : numbers)
		{
			int value = score / place % 10; // �Ώۂ̌���؂�o��
			place /= 10; // ��(��)��������

			number->SetValue(value); // �������X�V����
		}
	}

	//void Score::OnUpdate()
	//{

	//}

	void Score::OnDraw()
	{
		GameObject::OnDraw();// (SCORE�̕������\�������j
		for (auto& number : numbers) // �e���̐�����`�悷��
		{
			number->OnDraw();
		}
	}
}