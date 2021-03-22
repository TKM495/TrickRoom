/*!
@file StageLoad.h
@brief ステージのロード
*/

#pragma once
#include "stdafx.h"
#include "StageObject.h"

namespace basecross {
	//class StageLoad :public GameObject {
	//	vector<shared_ptr<StageObject>> m_stageObjects;
	//	map<wstring, uint16_t> m_objectTypeList;

	//public:
	//	StageLoad(const shared_ptr<Stage>& stage)
	//		:GameObject(stage)
	//	{}

	//	void OnDraw() override;

	//	template<class T>
	//	void AddStageObject(const Vec3& position) {
	//		auto object = ObjectFactory::Create<T>(GetStage());
	//		auto objectTrans = object->GetComponent<Transform>();
	//		objectTrans->SetPosition(position);
	//		m_stageObjects.push_back(object);
	//	}

	//	void Load(const wstring& filename);
	//	void SaveTextFile(const wstring& filename);
	//	void SaveBinaryFile(const wstring& filename);
	//};
}
//end basecross
