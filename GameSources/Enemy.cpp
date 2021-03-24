/*!
@file Enemy.cpp
@brief �G����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Enemy::Enemy(const shared_ptr<Stage>& stage,
		const wstring& line)
		:StageObject(stage)
	{
		//�g�[�N���i�J�����j�̔z��
		vector<wstring> tokens;
		Util::WStrToTokenVector(tokens, line, L',');
		//�e�g�[�N���i�J�����j���X�P�[���A��]�A�ʒu�ɓǂݍ���
		m_position = Vec3(
			(float)_wtof(tokens[1].c_str()),
			(float)_wtof(tokens[2].c_str()),
			(float)_wtof(tokens[3].c_str())
		);
		m_scale = Vec3(
			(float)_wtof(tokens[4].c_str()),
			(float)_wtof(tokens[5].c_str()),
			(float)_wtof(tokens[6].c_str())
		);
		m_rotation = Vec3(
			XMConvertToRadians((float)_wtof(tokens[7].c_str())),
			XMConvertToRadians((float)_wtof(tokens[8].c_str())),
			XMConvertToRadians((float)_wtof(tokens[9].c_str()))
		);
	}
	void Enemy::OnCreate() {
		auto drawComp = AddComponent<PNTStaticDraw>();
		drawComp->SetMeshResource(L"Enemy");

		auto collComp = AddComponent<CollisionSphere>();

		auto scene = App::GetApp()->GetScene<Scene>();
		if (scene->GetDebugState() == DebugState::Debug) {
			collComp->SetDrawActive(true);
		}

		auto transComp = GetComponent<Transform>();
		transComp->SetPosition(m_position);
		transComp->SetScale(m_scale);

		AddTag(L"damage");
	}

	void Enemy::OnUpdate() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += elapsedTime;
		if (m_TotalTime >= XM_2PI)
		{
			m_TotalTime = 0.0f;
		}

		auto ptrTrans = GetComponent<Transform>();
		float posX = sin(m_TotalTime) + m_Position.x;
		auto pos = ptrTrans->GetPosition();
		pos.x = posX;
		ptrTrans->SetPosition(pos);
	}
}
//end basecross