#include "stdafx.h"
#include "Project.h"

namespace basecross {
	int Bullet::count = 0;

	void Bullet::OnCreate()
	{
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");

		auto transComp = GetComponent<Transform>();
		float scale = 0.5f;
		transComp->SetScale(scale, scale, scale);

		AddComponent<CollisionSphere>();
		AddTag(L"damage");
		AddTag(L"Bullet");
	}

	void Bullet::OnUpdate()
	{
		auto& app = App::GetApp();
		float delta = app->GetElapsedTime(); // �f���^���ԁi�t���[���^�C���j
											 // �i�O�̃t���[������������̂ɂ����������ԁA
											 //   �܂�O�̃t���[������̌o�ߎ��ԁj
		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();
		auto forward = transComp->GetForword(); // �I�u�W�F�N�g�̐��ʂ�\���P�ʃx�N�g��
		auto state = dynamic_pointer_cast<GameStage>(GetStage())->GetState();
		auto camera = dynamic_pointer_cast<MainCamera>(OnGetDrawCamera());
		switch (state)
		{
		default:
			if (!camera->GetbLeapFlg()) {
				pos += forward * m_speed * delta; // �O���ɕb��10.0�ړ�����
			}
			break;
		case basecross::GameStage::GameState::PAUSE:
			break;
		}

		transComp->SetPosition(pos);
	}

	void Bullet::OnCollisionEnter(shared_ptr<GameObject>& other) {
		if (!other->FindTag(L"Battery")) {
			// ����
			GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());
		}
	}
}