/*!
@file Player.h
@brief �G�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Enemy_move : public GameObject 
	{
		Vec3 start = Vec3(0.0f);
		Vec3 end = Vec3(1.0f);

		float speed = 1.0f; // ����
		float distance_two; // ��_�̋���
		float A = 0;		
		bool Flg = false;   // �t���O

	public:
		Enemy_move(const std::shared_ptr<Stage>& stage) :
			GameObject(stage)
		{}

		void OnCreate() override;
		void OnUpdate() override;
	};
}