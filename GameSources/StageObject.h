/*!
@file StageObject.h
@brief ステージに配置するオブジェクトの基底クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	struct StageObjData {
		Vec3 position;
		Vec3 scale;
		Vec3 rotation;
	};

	class StageObject :public GameObject {
	protected:
		Vec3 m_position;
		Vec3 m_scale;
		Vec3 m_rotation;
	public:
		StageObject(const shared_ptr<Stage>& stage)
			:GameObject(stage)
		{}

		virtual void OnCreate()override;
		//virtual void OnUpdate()override {}
		//virtual void OnDraw()override {}
	};
}
//end basecross
