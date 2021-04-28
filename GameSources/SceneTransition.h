/*!
@file SceneTransition.h
@brief フェードイン、アウト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class SceneTransition :public GameObject {
	public:
		enum class TransDir {
			In,
			Out
		};
	private:
		enum class TransState {
			Active,
			Stop
		};
		//フェードの状態
		TransState m_state;
		//フェードの方向(フェードインなら-1,アウトなら1)
		int m_key;
		//フェードにかかる時間
		float m_Time;
		//時間計測用
		float m_delta;
		//最大サイズ
		float m_maxSize;
		float m_start;
		float m_end;
		void SetSize(float size);
		void SetRotation(float deg);
	public:
		SceneTransition(const shared_ptr<Stage>& stage)
			:GameObject(stage),
			m_state(TransState::Stop),
			m_Time(1.0f),
			m_delta(0.0f),
			m_key(0),
			m_maxSize(30.0f),
			m_start(0.0f),
			m_end(0.0f)
		{}
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void Play(TransDir dir);

		void SetTransitionTime(float time) {
			m_Time = time;
		}

		float GetTransitionTime() {
			return m_Time;
		}

		//動作しているかのフラグ
		bool GetTransitionActive() {
			return m_state == TransState::Active ? true : false;
		}
	};

}
//end basecross
