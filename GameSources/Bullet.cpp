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

		pos += forward * 10.0f * delta; // �O���ɕb��10.0�ړ�����

		transComp->SetPosition(pos);
	}

	void Bullet::OnCollisionEnter(shared_ptr<GameObject>& other) {
		// ����
		GetStage()->RemoveGameObject<Bullet>(GetThis<Bullet>());
	}
}