#pragma once
#include "stdafx.h"
#include "Player.h"

namespace basecross {
	class PlayerModel :public GameObject {
		shared_ptr<Player> m_player;
		float m_delta;
	public:
		PlayerModel(const shared_ptr<Stage>& stage,
			const shared_ptr<Player> player)
			:GameObject(stage),
			m_player(player), m_delta(0.0f)
		{}

		void OnCreate()override;
		void OnUpdate()override;
	};
}