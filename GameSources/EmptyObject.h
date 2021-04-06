/*!
@file EmptyObject.h
@brief 中身のないオブジェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class EmptyObject :public GameObject {
		wstring m_tag;
	public:
		EmptyObject(const shared_ptr<Stage>& stage,
			const wstring& tag)
			:GameObject(stage),
			m_tag(tag)
		{}

		void OnCreate()override;

	};

}
//end basecross
