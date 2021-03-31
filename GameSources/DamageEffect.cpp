#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void DamageEffect::OnCreate()
	{
		auto draw = AddComponent<PNTStaticDraw>();
		draw->SetMeshResource(L"DEFAULT_SPHERE");
		// draw->SetTextureResource(L"spark"); // もしもエフェクトにテクスチャを貼り付けるなら必要

		auto trans = AddComponent<Transform>();
		trans->SetScale(0.2f, 0.2f, 0.2f);
		//auto mat = trans->GetWorldMatrix();

		//PsSphereParam param(mat, 1.0f, false, PsMotionType::MotionTypeActive);
		//auto rigid = AddComponent<RigidbodySphere>(param);
		//rigid->SetAutoGravity(true);

	}

	void DamageEffect::OnUpdate()
	{

		auto transComp = AddComponent<Transform>();
		auto trans = transComp->GetPosition();

		transComp->SetPosition(trans.x + 0.01f, trans.y + jumpforce, 0.0f);

		if (jumpforce > -1.05f) jumpforce -= 0.01f;
	}
}