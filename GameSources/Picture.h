/*!
@file Picture.h
@brief ���͋C���o�����߂̊G
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Picture :public StageObject {
		//�e�N�X�`���^�O
		wstring m_texName;
	public:
		Picture(const shared_ptr<Stage>& stage,
			const wstring& line);

		virtual void OnCreate()override;

	};
}
//end basecross
