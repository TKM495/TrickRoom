/*!
@file Effect.cpp
@brief エフェクトなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Effect::InsertEffect(const Vec3& Pos) {
		InsertEffect(Pos, Col4(1.0f, 0.0f, 0.0f, 1.0f));
	}

	void Effect::InsertEffect(const Vec3& Pos, Col4 color)
	{
		auto ParticlePtr = InsertParticle(4);
		ParticlePtr->SetEmitterPos(Pos + m_offset);
		ParticlePtr->SetTextureResource(L"Spark");
		ParticlePtr->SetMaxTime(0.5f);
		for (auto& rParticleSprite : ParticlePtr->GetParticleSpriteVec()) {
			rParticleSprite.m_LocalPos.x = Util::RandZeroToOne() * 0.1f - 0.05f;
			rParticleSprite.m_LocalPos.y = Util::RandZeroToOne() * 0.1f;
			rParticleSprite.m_LocalPos.z = Util::RandZeroToOne() * 0.1f - 0.05f;
			//各パーティクルの移動速度を指定
			rParticleSprite.m_Velocity = Vec3(
				rParticleSprite.m_LocalPos.x * 25.0f,
				rParticleSprite.m_LocalPos.y * 25.0f,
				rParticleSprite.m_LocalPos.z * 25.0f
			);

			rParticleSprite.m_LocalScale = Vec3(1.5f);
			//色の指定
			rParticleSprite.m_Color = color;
		}
	}
}