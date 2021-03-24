/*!
@file Player.cpp
@brief “G‚È‚Ç‚ÌŽÀ‘Ì
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	void Enemy::OnCreate() 
	{
		auto drawComp = AddComponent<BcPNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_SPHERE");

		//auto ptr = GetComponent<Transform>();
		//ptr->SetPosition(Vec3(0.0f, 0.0f, 0.0f));
	}

	void Enemy::OnUpdate()
	{
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += elapsedTime;
		if (m_TotalTime >= XM_2PI)
		{
			m_TotalTime = 0.0f;
		}

		auto ptrTrans = GetComponent<Transform>();
		float posX = sin(m_TotalTime) + m_Position.x;
		auto pos = ptrTrans->GetPosition();
		pos.x = posX;
		ptrTrans->SetPosition(pos);
	}
}