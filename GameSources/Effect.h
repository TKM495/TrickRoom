/*!
@file Effect.h
@brief エフェクトなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Effect : public MultiParticle
	{
		Vec3 m_offset;
	public:
		Effect(const std::shared_ptr<Stage>& stage,
			const Vec3& offset)
			: MultiParticle(stage),
			m_offset(offset)
		{

		}

		void InsertEffect(const Vec3& Pos);
		void InsertEffect(const Vec3& Pos, Col4 color);
	};
}