/*!
@file StaticPlatePolygon.h
@brief ���͋C���o�����߂̊G
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"

namespace basecross {
	class StaticPlatePolygon :public StageObject, public TrickArtBase {
		//�e�N�X�`���^�O
		wstring m_texName;
	public:
		StaticPlatePolygon(const shared_ptr<Stage>& stage,
			const wstring& line);
		StaticPlatePolygon(const shared_ptr<Stage>& stage,
			const wstring& texName, const ObjectParam& param);

		void OnCreate()override;
	};
}
//end basecross
