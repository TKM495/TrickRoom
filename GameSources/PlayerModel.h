#pragma once
#include "stdafx.h"
#include "Player.h"
#include "TimeCounter.h"

namespace basecross {
	class PlayerModel :public GameObject {
		shared_ptr<Player> m_player;
		Col4 col1, col2;
		TimeCounter m_timer;
	public:
		PlayerModel(const shared_ptr<Stage>& stage,
			const shared_ptr<Player> player)
			:GameObject(stage),
			m_player(player)
		{}

		void OnCreate()override;
		void OnUpdate()override;

		void Motion(float delta);
	};
}