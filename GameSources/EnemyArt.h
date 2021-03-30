/*!
@file EnemyArt.h
@brief トリックアートの敵クラス
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"
#include "MainCamera.h"

namespace basecross {
	class EnemyArt :public TrickArtBase {
		state m_activeState;
		wstring m_behavior;
		float m_cycle;
		float m_speed;
		float m_offset;
	public:
		EnemyArt(const shared_ptr<Stage>& stage,
			const wstring& line);

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		void OnCollisionEnter(shared_ptr<GameObject>& other) override;

	};

}
//end basecross
