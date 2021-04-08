/*!
@file Result.cpp
@brief 結果実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Result::OnCreate() {
		wstring titleStr = L"";
		int clearflg = 0;
		switch (m_data.state)
		{
		case GameStage::GameState::CLEAR:
			titleStr = L"StageClear";
			clearflg = 1;
			break;
		case GameStage::GameState::GAMEOVER:
			titleStr = L"GameOver";
			clearflg = 0;
			break;
		default:
			//エラー
			break;
		}

		//生の値
		ScorePoints score{
			m_data.HP,
			m_data.RCrystal,
			m_data.BCrystal,
			m_data.Distance,
			clearflg
		};
		//かかる倍率
		ScorePoints factor{
			500,	//HP
			750,	//赤のクリスタル
			250,	//青のクリスタル
			100,	//距離
			1000,	//クリアボーナス
			1		//トータルスコア
		};
		score = score * factor;

		score.CountTotal(); //初期化の内容から合計を計算

		//タイトルは一つなので別処理
		auto title = GetStage()->AddGameObject<StringSprite2>(titleStr);
		title->GetComponent<Transform>()->SetPosition(Vec3(0.0f, 320.0f, 0.0f));

		vector<ResultParam> params{
			{Vec2(-500.0f,210.0f),SpriteType::String,L"RemainLife",Align::Horizontal::Left},
			{Vec2(50.0f,210.0f),SpriteType::Number,Util::IntToWStr(m_data.HP),Align::Horizontal::Right},
			{Vec2(100.0f,210.0f),SpriteType::String,L"X"},
			{Vec2(350.0f,210.0f),SpriteType::Number,Util::IntToWStr(factor.HP),Align::Horizontal::Right},
			{Vec2(-50.0f,210.0f),SpriteType::Image,L"1000,70",Align::Horizontal::Center,Align::Vertical::Center},

			{Vec2(-500.0f,130.0f),SpriteType::String,L"Crystal",Align::Horizontal::Left},
			{Vec2(50.0f,130.0f),SpriteType::Number,Util::IntToWStr(m_data.BCrystal),Align::Horizontal::Right},
			{Vec2(100.0f,130.0f),SpriteType::String,L"X"},
			{Vec2(350.0f,130.0f),SpriteType::Number,Util::IntToWStr(factor.BCrystal),Align::Horizontal::Right},
			{Vec2(50.0f,50.0f),SpriteType::Number,Util::IntToWStr(m_data.RCrystal),Align::Horizontal::Right},
			{Vec2(100.0f,50.0f),SpriteType::String,L"X"},
			{Vec2(350.0f,50.0f),SpriteType::Number,Util::IntToWStr(factor.RCrystal),Align::Horizontal::Right},

			{Vec2(-500.0f,-30.0f),SpriteType::String,L"FromStart",Align::Horizontal::Left},
			{Vec2(150.0f,-30.0f),SpriteType::Number,Util::IntToWStr(m_data.Distance),Align::Horizontal::Right},

			{Vec2(-500.0f,-100.0f),SpriteType::String,L"ClearBonus",Align::Horizontal::Left},
			{Vec2(150.0f,-100.0f),SpriteType::Number,Util::IntToWStr(score.ClearBonus),Align::Horizontal::Right},

			{Vec2(-500.0f,-170.0f),SpriteType::String,L"TotalScore",Align::Horizontal::Left},
			{Vec2(150.0f,-170.0f),SpriteType::Number,Util::IntToWStr(score.Total),Align::Horizontal::Right}
		};

		for (auto& param : params) {
			switch (param.type)
			{
			case SpriteType::String:
				CreateString(param);
				break;
			case SpriteType::Image:
				CreateImage(param);
				break;
			case SpriteType::Number:
				CreateNumber(param);
				break;
			}
		}
	}

	void Result::CreateString(ResultParam& param) {
		auto str = GetStage()->AddGameObject<StringSprite2>(param.value, param.horizontal, param.vertical);
		auto transComp = str->GetComponent<Transform>();
		transComp->SetPosition((Vec3)param.pos);
		transComp->SetScale(Vec3(m_strSize, m_strSize, 1.0f));
	}
	void Result::CreateImage(ResultParam& param) {
		vector<wstring> tokens;
		Util::WStrToTokenVector(tokens, param.value, L',');

		auto size = Vec2((float)_wtof(tokens[0].c_str()), (float)_wtof(tokens[1].c_str()));


		auto image = GetStage()->AddGameObject<FrameSprite>(size);
		image->SetPosition(param.pos);
		image->SetDrawLayer(-1);
	}
	void Result::CreateNumber(ResultParam& param) {
		Vec3 offset(0.0f);
		int key = 0;

		for (int i = 0; i < param.value.size(); i++)
		{
			char c = '0';
			switch (param.horizontal)
			{
			case Align::Horizontal::Right:
				c = param.value[param.value.size()-1 - i];
				key = -1;
				break;
			case Align::Horizontal::Left:
				c = param.value[i];
				key = 1;
				break;
			default:
				c = param.value[i];
				key = 1;
				break;
			}

			auto num = GetStage()->AddGameObject<Numbers>((int)c - '0');
			auto transComp = num->GetComponent<Transform>();
			transComp->SetPosition((Vec3)param.pos + offset);
			transComp->SetScale(Vec3(m_numSize, m_numSize, 1.0f));
			offset += Vec3(60.0f * key, 0, 0); // 数字の幅の文
		}
	}
}
//end basecross
