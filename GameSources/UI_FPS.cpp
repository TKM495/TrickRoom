/*!
@file UI_FPS.cpp
@brief �t���[�����[�gUI����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void UI_FPS::OnCreate() {
		SetDrawLayer(10);

		//�f�o�b�O�p�̕������\�����邽�߂̃R���|�[�l���g��ǉ�
		auto ssComp = AddComponent<StringSprite>();
		ssComp->SetBackColor(Col4(0.0f, 0.0f, 0.0f, 0.0f)); //������̕\���̈�̔w�i�F��ύX
		ssComp->SetTextRect(Rect2D<float>(10, 10, 100, 50)); //������\���̈�̃T�C�Y��ύX
		ssComp->SetText(L"");
	}

	void UI_FPS::OnUpdate() {
		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring FPS(L"FPS: ");
		FPS += Util::UintToWStr(fps);

		auto ssComp = GetComponent<StringSprite>();
		ssComp->SetText(FPS);
	}
}
//end basecross
