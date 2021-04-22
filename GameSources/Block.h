/*!
@file Block2.h
@brief �u���b�N
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"
#include "TrickArtSystem/TrickArtSystem.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class Block : public GameObject;
	//--------------------------------------------------------------------------------------
	class Block : public StageObject, public TrickArtBase {
	public:
		//�\�z�Ɣj��
		Block(const shared_ptr<Stage>& StagePtr,
			const wstring& line);
		virtual ~Block();
		//������
		virtual void OnCreate() override;
		//����
		virtual void OnUpdate() override;
	};
}
//end basecross
