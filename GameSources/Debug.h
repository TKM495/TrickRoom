#pragma once
#include "stdafx.h"

namespace basecross {
	class Debug :public GameObject {
		std::wstringstream wss; //�f�o�b�O�p������
	public :
		Debug(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{
		}
		void OnCreate()override;
		void OnUpdate()override;
	};
}