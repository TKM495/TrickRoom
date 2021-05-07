/*!
@file Spikes.h
@brief ž™
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"
#include "TrickArtSystem/TrickArtSystem.h"

namespace basecross {
	class Spikes :public StageObject ,public TrickArtBase{
	public:
		Spikes(const shared_ptr<Stage>& stage,
			const wstring& line);

		void OnCreate()override;
		void OnUpdate()override;
	};

}
//end basecross
