/*!
@file Plane.h
@brief 板オブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Plane :public StageObject ,public TrickArtBase{
		wstring m_texName;
	public:
		Plane(shared_ptr<Stage>& stage,
			const wstring& line);
		//Plane(shared_ptr<Stage>& stage,
		//	const Vec3& pos,
		//	const Vec3& scale,
		//	const Vec3& rot)
		//	:StageObject(stage),
		//	TrickArtBase(stage)
		//{
		//	m_position = pos;
		//	m_scale = scale;
		//	m_rotation = rot;
		//}

		virtual void OnCreate()override;
	};
}
//end basecross
