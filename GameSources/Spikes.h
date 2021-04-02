/*!
@file Spikes.h
@brief ž™
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Spikes :public StageObject {
	public:
		Spikes(const shared_ptr<Stage>& stage,
			const wstring& line);

		virtual void OnCreate()override;
	};

}
//end basecross
