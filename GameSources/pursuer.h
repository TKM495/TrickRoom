/*!
@file pursuer.h
@brief 追いかけてくる敵など
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Pursuer : public StageObject
	{
		float m_Speed;
		void Move();
		Vec3 MoveVec();

	public:
		Pursuer(const std::shared_ptr<Stage>& stage,
			const wstring& line);

	public:
		void OnCreate() override;
		void OnUpdate() override;

		Vec3 GetPos();
	};
}