/*!
@file Player.h
@brief “G‚È‚Ç
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Enemy_move : public GameObject 
	{
		Vec3 start = Vec3(0.0f);
		Vec3 end = Vec3(1.0f);

		float speed = 1.0f; // ‘¬‚³
		float distance_two; // “ñ“_‚Ì‹——£
		float A = 0;		
		bool Flg = false;   // ƒtƒ‰ƒO

	public:
		Enemy_move(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
		{}

		void OnCreate() override;
		void OnUpdate() override;
	};
}