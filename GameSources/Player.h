/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"
//#include "InputHandler.h"

namespace basecross{
	class Player : public StageObject {

		//InputHandler<Player> m_InputHandler;

		Vec3 m_Speed;//移動
		int m_HP;//HP(初期値５)
		float m_crystal;

		//Vec3 jumpVelocity;
		//private: bool bJump = false;
	public:
		Player(const std::shared_ptr<Stage>& stage,
			const wstring& line);

		void OnCreate() override;
		void OnUpdate() override;
		void SetSpeed();

		//HP
		void SetHP(int HP);
		int GetHP();
		//Crystal
		float GetCrystal();

		//void OnPushA();
		//void OnPushB(){}
		//void OnPushX() {}
		//void OnPushY() {}
		//void OnPushStart(){}
		//void OnPushBack() {}

	};
}
//end basecross

