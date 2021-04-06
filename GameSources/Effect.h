/*!
@file Effect.h
@brief エフェクトなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Effect : public MultiParticle
	{
	public:
		Effect(const std::shared_ptr<Stage>& stage)
			: MultiParticle(stage)
		{

		}

		void InsertEffect(const Vec3& Pos);
		void CrystalEffect(const Vec3& Pos);

	};
}