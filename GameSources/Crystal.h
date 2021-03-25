#pragma once
#include "stdafx.h"

namespace basecross {


	class Crystal : public GameObject {
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
	public:
		//\’z‚Æ”jŠü
		Crystal(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);
		//‰Šú‰»
		virtual void OnCreate() override;
		//‘€ì
	};

}
//end basecross
