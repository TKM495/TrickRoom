/*!
@file VirtualFloor.h
@brief ���z��(�e�N�X�`�����\��Ȃ��I�u�W�F�N�g�ɓ\��p)�N���X
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"

namespace basecross {
	class VirtualFloor :public StageObject, public TrickArtBase {
	public:
		VirtualFloor(const shared_ptr<Stage>& stage,
			const wstring& line);

		void OnCreate()override;
	};
}
//end basecross