#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Debug::OnCreate() {
		auto debug = GetThis<Debug>();
		GetStage()->SetSharedGameObject(L"Debug", debug);
		debug->SetDrawLayer(10);

		//�f�o�b�O�p�̕������\�����邽�߂̃R���|�[�l���g��ǉ�
		auto ssComp = AddComponent<StringSprite>();
		ssComp->SetBackColor(Col4(0.0f, 0.0f, 0.0f, 0.2)); //������̕\���̈�̔w�i�F��ύX
		ssComp->SetTextRect(Rect2D<float>(10, 10, 300, 400)); //������\���̈�̃T�C�Y��ύX
		ssComp->SetText(wss.str());
	}

	void Debug::OnUpdate() {
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto transComp = player->GetComponent<Transform>();
		auto pos = transComp->GetPosition();

		auto pursuer = GetStage()->GetSharedGameObject<Pursuer>(L"Pursuer");

		auto pursuerPos = pursuer->GetPos();
		auto myPos = player->GetComponent<Transform>()->GetPosition();
		auto dir = pursuerPos.x - myPos.x;

		//�I�u�W�F�N�g��
		auto ObjCount = GetStage()->GetGameObjectVec().size();
		wstring OBJ_COUNT(L"OBJ_COUNT: ");
		OBJ_COUNT += Util::UintToWStr((UINT)ObjCount);
		OBJ_COUNT += L"\n";
		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring FPS(L"FPS: ");
		FPS += Util::UintToWStr(fps);
		FPS += L"\nElapsedTime: ";
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		FPS += Util::FloatToWStr(ElapsedTime);
		FPS += L"\n";

		auto viewport = GetTypeStage<GameStage>()->GetView()->GetTargetViewport();
		wstring ViewStr(L"View:\n");
		ViewStr += L"Width=" + Util::FloatToWStr(viewport.Width, 6, Util::FloatModify::Fixed) + L",\t";
		ViewStr += L"Height=" + Util::FloatToWStr(viewport.Height, 6, Util::FloatModify::Fixed) + L",\n";

		wss.str(L"");
		wss << FPS;
		wss << L"PlayerPos:" << pos.x << L"," << pos.y << L"," << pos.z << endl;
		wss << L"Dir:" << dir << endl;
		wss << L"Pursuer:" << pursuerPos.x << endl;
		wss << ViewStr << OBJ_COUNT << endl;

		auto ssComp = GetComponent<StringSprite>();
		ssComp->SetText(wss.str());
	}
}