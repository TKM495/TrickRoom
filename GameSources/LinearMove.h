#pragma once
#include "stdafx.h"

namespace basecross {
	class LinerMove :public Behavior {
		Vec3 start = Vec3(0.0f);
		Vec3 end = Vec3(1.0f);

		float speed = 1.0f; // 速さ
		float distance_two; // 二点の距離
		float A = 0;
		bool Flg = false;   // フラグ
	public:
		LinerMove(const shared_ptr<GameObject>& obj)
			:Behavior(obj)
		{}

		void OnCreate()override;
		void Excute();
		void SetSpeed(float _speed) {
			speed = _speed;
		}
		void SetMovePositions(Vec3 _start, Vec3 _end) {
			start = _start;
			end = _end;
		}
		void SetOffset(float offset) {
			A = offset;
		}
	};
}