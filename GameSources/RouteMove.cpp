/*!
@file RouteMove.cpp
@brief ƒ‹[ƒg‚É‰ˆ‚Á‚½“®‚«‚È‚Ç
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {
	void RouteMove::Excute()
	{
		auto stage = GetStage();

		auto transComp = GetGameObject()->GetComponent<Transform>();
		auto pos = transComp->GetPosition();

		const auto& app = App::GetApp();
		float ElapsedTime = app->GetElapsedTime();

		if (!bHitFlg && bjudgment)
		{
			auto Move = m_Speed * ElapsedTime;
			pos += Vec3(0.0f, 0.0f, Move);
			transComp->SetPosition(pos);
		}

		if (bHitFlg && bjudgment)
		{
			auto Move = m_Speed * ElapsedTime;
			pos += Vec3(-Move, 0.0f, 0.0f);
			transComp->SetPosition(pos);
			//m_counter += 1 * ElapsedTime;
		}

		if (!bHitFlg && !bjudgment)
		{
			auto Move = m_Speed * ElapsedTime;
			pos += Vec3(0.0f, 0.0f, -Move);
			transComp->SetPosition(pos);
		}

		if (bHitFlg && !bjudgment)
		{
			auto Move = m_Speed * ElapsedTime;
			pos += Vec3(Move, 0.0f, 0.0f);
			transComp->SetPosition(pos);
			//m_counter += 1 * ElapsedTime;
		}
	}

	void RouteMove::Hit(bool flg)
	{
		//auto bWallTag = other->FindTag(L"Wall");
		//auto bWallTag = other->FindTag(L"Wall");
		//auto bWallTag2 = other->FindTag(L"Wall2");


		//if (bWallTag)//•Ç‚É“–‚½‚Á‚½‚ç
		//{
		//	bHitFlg = true;
		//}

		//if (bWallTag2)
		//{
		//	bwalljudg = true;
		//}

		//if (bHitFlg && bwalljudg && bjudgment)
		//{
		//	bHitFlg = false;
		//	m_counter = 0;
		//	bjudgment = false;
		//	bwalljudg = false;
		//}

		//if (bHitFlg && bwalljudg && !bjudgment)
		//{
		//	bHitFlg = false;
		//	m_counter = 0;
		//	bjudgment = true;
		//	bwalljudg = false;
		//}
	}
}
