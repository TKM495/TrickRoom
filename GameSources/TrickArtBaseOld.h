/*!
@file TrickArtBaseOld.h
@brief �g���b�N�A�[�g�̊��N���X
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"

namespace basecross {
	class TrickArtBaseOld :public StageObject {
	protected:
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;
		vector<shared_ptr<AdvCollision>> m_myCols;
		wstring m_texStr;
		Vec3 m_artSize;
		state m_activeState;
	public:
		TrickArtBaseOld(const shared_ptr<Stage>& stage)
			:StageObject(stage)
		{}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};
}
//end basecross
