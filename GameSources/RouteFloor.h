/*!
@file RouteFloor.h
@brief
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"
#include "TrickArtSystem/TrickArtSystem.h"

namespace basecross {
	class RouteFloor : public StageObject, public TrickArtBase {
	public:
		RouteFloor(const shared_ptr<Stage>& StagePtr,
			const wstring& line);
		virtual ~RouteFloor();
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};
}
//end basecross
