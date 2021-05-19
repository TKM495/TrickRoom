/*!
@file GoalStage.cpp
@brief
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void GoalStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		auto PtrCamera = ObjectFactory::Create<GoalCamera>();
		PtrView->SetCamera(PtrCamera);
		auto PtrMultiLight = CreateLight<MultiLight>();
		PtrMultiLight->SetDefaultLighting();
	}

	void GoalStage::OnCreate() {
		CreateViewLight();

		GameObjecttCSVBuilder builder;
		builder.Register<Player>(L"Player");
		builder.Register<Plane>(L"Plane");
		builder.Register<Block>(L"Block");
		builder.Register<Battery>(L"Battery");
		builder.Register<Goal>(L"Goal");

		auto dir = App::GetApp()->GetDataDirWString();
		auto path = dir + L"Csv/Stage/Stage";
		path += to_wstring(m_stageNum);
		path += L".csv";
	}
}
//end basecross