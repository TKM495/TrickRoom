#pragma once
#include "stdafx.h"

namespace basecross {
	class Debug :public GameObject {
		std::wstringstream wss; //�f�o�b�O�p������
		wstring m_wstr;
	public :
		Debug(const shared_ptr<Stage>& stage)
			:GameObject(stage),
			m_wstr(L"")
		{
		}
		void OnCreate()override;
		void OnUpdate()override;
		void SetString(wstring str) {
			m_wstr += str;
		}
	};
}