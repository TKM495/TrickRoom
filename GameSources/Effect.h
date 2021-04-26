/*!
@file Effect.h
@brief �G�t�F�N�g�Ȃ�
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
		void InsertEffect(const Vec3& Pos, Col4 color);
		void CrystalEffect(const Vec3& Pos);

	};
}