/*!
@file Block2.h
@brief ブロック
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	class Block : public GameObject;
	//--------------------------------------------------------------------------------------
	class Block : public StageObject {
	public:
		//構築と破棄
		Block(const shared_ptr<Stage>& StagePtr,
			const wstring& line);
		virtual ~Block();
		//初期化
		virtual void OnCreate() override;
		//操作
	};

}
//end basecross
