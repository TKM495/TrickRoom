/*!
@file illusionModel.h
@brief çˆéãÉÇÉfÉã
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"

namespace basecross {
	class illusionModel :public GameObject {
	public:
		enum class Type {
			Triangle,
			Stairs,
			Cube,
			Arch,
			Rectangle
		};
	private:
		Type m_type;
		Vec3 m_position;
		Vec3 m_scale;
		Vec3 m_rotation;
	public:
		illusionModel(const shared_ptr<Stage>& stage, Type type)
			:GameObject(stage),
			m_position(Vec3(0.0f)), m_scale(Vec3(1.0f)), m_rotation(Vec3(0.0f)),
			m_type(type)
		{}
		illusionModel(const shared_ptr<Stage>& stage,
			ObjectParam param,
			Type type)
			:GameObject(stage),
			m_position(param.position),
			m_scale(param.scale),
			m_rotation(param.rotation),
			m_type(type)
		{}

		void OnCreate()override;
	};
}
//end basecross