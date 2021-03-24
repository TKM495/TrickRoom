/*!
@file TrickArtBase.h
@brief トリックアートの基底クラス
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"

namespace basecross {
	class TrickArtBase :public StageObject {
	protected:
		vector<VertexPositionColorTexture> m_vertices;
		vector<uint16_t> m_indices;
		vector<shared_ptr<AdvCollision>> m_myCols;
		wstring m_texStr;
		Vec3 m_artSize;
		state m_activeState;
	public:
		TrickArtBase(const shared_ptr<Stage>& stage)
			:StageObject(stage)
		{}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};
}
//end basecross
