#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Goal::OnCreate()
	{
		auto drawComp = AddComponent<BcPNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");
		

		auto TransComp = GetComponent<Transform>();
		
		TransComp->SetPosition(0.0f, 0.0f, 0.0f);
		TransComp->SetScale(1.0f, 2.0f, 0.2f);

		}

}
