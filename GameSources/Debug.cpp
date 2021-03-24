#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Debug::OnCreate() {
		//�f�o�b�O�p�̕������\�����邽�߂̃R���|�[�l���g��ǉ�
		auto ssComp = AddComponent<StringSprite>();
		ssComp->SetBackColor(Col4(0.0f, 0.0f, 0.0f, 0.5)); //������̕\���̈�̔w�i�F��ύX
		ssComp->SetTextRect(Rect2D<float>(10, 10, 300, 200)); //������\���̈�̃T�C�Y��ύX
	}

	void Debug::OnUpdate() {
		auto ssComp = GetComponent<StringSprite>();
		wss.str(L"");
		wss << m_wstr << endl;
		ssComp->SetText(wss.str());
	}
}