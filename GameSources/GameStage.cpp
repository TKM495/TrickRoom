/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<MainCamera>();
		PtrView->SetCamera(PtrCamera);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			AddGameObject<Debug>();


			//AddGameObject<Timer>();
			AddGameObject<UI_HP>();
			AddGameObject<UI_Crystal>();

			//�Q�[���I�u�W�F�N�g�r���_�[
			GameObjecttCSVBuilder builder;
			//�Q�[���I�u�W�F�N�g�̓o�^
			builder.Register<Player>(L"Player");
			builder.Register<Plane>(L"Plane");
			builder.Register<Pillar>(L"Pillar");
			builder.Register<Block>(L"Block");
			builder.Register<BlockArt>(L"BlockArt");
			builder.Register<Enemy>(L"Enemy");
			builder.Register<EnemyArt>(L"EnemyArt");
			builder.Register<Spikes>(L"Spikes");
			builder.Register<SpikesArt>(L"SpikesArt");
			builder.Register<Stairs>(L"Stairs");
			builder.Register<StairsArt>(L"StairsArt");
			builder.Register<FloorArt>(L"FloorArt");
			builder.Register<PoleArt>(L"PoleArt");
			builder.Register<Crystal>(L"Crystal");
			//builder.Register<FloorGenerator>(L"FloorGenerator");

			auto& app = App::GetApp();
			auto dir = app->GetDataDirWString();
			auto path = dir + L"Csv/Object.csv";
			//auto& app = App::GetApp();
			//auto dir = app->GetDataDirWString();
			//auto path = dir + L"Csv/Object";
			//path += scene->GetNum();
			//path += L".csv";

			builder.Build(GetThis<Stage>(), path);

			auto stagePar = AddGameObject<StageParent>();

			vector<shared_ptr<GameObject>> stageObjs;
			GetUsedTagObjectVec(L"StageObject", stageObjs);
			for (auto& obj : stageObjs) {
				obj->GetComponent<Transform>()->SetParent(stagePar);
			}
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::OnUpdate() {
		auto delta = App::GetApp()->GetElapsedTime();
		if (m_delta > 0.05f) {
			ObjDraw();
			m_delta = 0.0f;
		}
		m_delta += delta;
	}

	void GameStage::ObjDraw() {
		vector<shared_ptr<GameObject>> stageObjs;
		GetUsedTagObjectVec(L"StageObject", stageObjs);
		auto camera = dynamic_pointer_cast<MainCamera>(GetView()->GetTargetCamera());
		auto playerPos = camera->GetAt();
		for (auto& obj : stageObjs) {
			if (obj->FindTag(L"Plane") || obj->FindNumTag(-1)) {
				continue;
			}

			auto pos = obj->GetComponent<Transform>()->GetPosition();
			auto dir = playerPos - pos;
			if (dir.lengthSqr() > m_renderDis * m_renderDis) {
				obj->SetDrawActive(false);
				obj->SetUpdateActive(false);
			}
			else {
				obj->SetDrawActive(true);
				obj->SetUpdateActive(true);
			}
		}
	}

}
//end basecross
