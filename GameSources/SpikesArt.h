/*!
@file SpikesArt.h
@brief �g���b�N�A�[�g�̞��N���X
*/

#pragma once
#include "stdafx.h"
#include "TrickArtBaseOld.h"
#include "MainCamera.h"

namespace basecross {
	class SpikesArt :public TrickArtBaseOld {
	public:
		SpikesArt(const shared_ptr<Stage>& stage,
			const wstring& line);

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}
//end basecross
