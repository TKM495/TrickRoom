/*
@file Block.h
@brief ÉuÉçÉbÉN
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"
#include "TrickArtSystem/TrickArtSystem.h"

namespace basecross {
	class Block : public StageObject, public TrickArtBase {
		bool m_bShadow;
	public:
		Block(const shared_ptr<Stage>& StagePtr,
			const wstring& line);
		virtual ~Block();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}
//end basecross