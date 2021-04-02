#pragma once
#include "stdafx.h"

namespace basecross {
	class Debug :public GameObject {
		std::wstringstream wss; //デバッグ用文字列
	public :
		Debug(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{
		}
		void OnCreate()override;
		void OnUpdate()override;
	};
}