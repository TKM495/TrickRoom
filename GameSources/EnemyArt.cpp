/*!
@file EnemyArt.cpp
@brief トリックアートの敵クラス実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	EnemyArt::EnemyArt(const shared_ptr<Stage>& stage,
		const wstring& line)
		:TrickArtBase(stage)
	{
		//トークン（カラム）の配列
		vector<wstring> tokens;
		Util::WStrToTokenVector(tokens, line, L',');
		//各トークン（カラム）をスケール、回転、位置に読み込む
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
		m_activeState = tokens[10] == L"Right" ? state::Right : state::Left;
		m_texStr = tokens[11].c_str();

		m_behavior = tokens[12];
		m_cycle = (float)_wtof(tokens[13].c_str());
		m_speed = (float)_wtof(tokens[14].c_str());
		m_offset = (float)_wtof(tokens[15].c_str());
	}

	void EnemyArt::OnCreate() {
		//色のデータ(R,G,B,A)
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		//頂点のデータ (番号は左上から右下まで)
		m_vertices = {
			{Vec3(-1.0f, 0.0f,+1.0f),color,Vec2(0.0f,0.0f)}, //0
			{Vec3(+1.0f, 0.0f,+1.0f),color,Vec2(1.0f,0.0f)}, //1
			{Vec3(-1.0f, 0.0f,-1.0f),color,Vec2(0.0f,1.0f)}, //2
			{Vec3(+1.0f, 0.0f,-1.0f),color,Vec2(1.0f,1.0f)}  //3
		};
		//頂点インデックス(頂点をつなげる順番)
		m_indices = {
			0, 1, 2, //上の三角形
			2, 1, 3  //下の三角形
		};

		TrickArtBase::OnCreate();

		auto obbComp = AddComponent<CollisionObb>();
		//obbComp->SetFixed(true);
		obbComp->SetAfterCollision(AfterCollision::None);

		auto scene = App::GetApp()->GetScene<Scene>();
		if (scene->GetDebugState() == DebugState::Debug) {
			obbComp->SetDrawActive(true);
		}
		//obbComp->SetAfterCollision(AfterCollision::None);

		if (m_behavior == L"SinCurve") {
			GetBehavior<SinCurve>()->SetOffset(m_offset);
		}
		else {

		}


		//当たり判定の切り替えでダメージの判定を行うため
		//常にこのタグを持つ
		AddTag(L"damage");
	}

	void EnemyArt::OnUpdate() {
		auto camera = dynamic_pointer_cast<MainCamera>(OnGetDrawCamera());
		state nowState = camera->GetCamState();
		if (nowState == m_activeState) {
			GetComponent<CollisionObb>()->SetUpdateActive(true);
		}
		else {
			GetComponent<CollisionObb>()->SetUpdateActive(false);
		}

		auto state = dynamic_pointer_cast<GameStage>(GetStage())->GetState();
		switch (state)
		{
		case basecross::GameStage::GameState::PLAYING:
			if (camera->GetbLeapFlg()) {
				return;
			}

			if (m_behavior == L"SinCurve") {
				GetBehavior<SinCurve>()->Excute(m_cycle, m_speed);
			}
			else {

			}
			break;
		case basecross::GameStage::GameState::PAUSE:
			break;
		}

	}

	void EnemyArt::OnCollisionEnter(shared_ptr<GameObject>& other) {
		//判定条件がdamageのタグがあればいいのでこの処理はコメントアウト
		//auto player = dynamic_pointer_cast<Player>(other);
		//if (player) {
		//	return;
		//}

		//オブジェクトを消してもいいと思ったが、念のため
		if (other->FindTag(L"damage")) {
			SetDrawActive(false);
			SetUpdateActive(false);
			AddNumTag(-1);
		}
	}
}
//end basecross