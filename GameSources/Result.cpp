/*!
@file Result.cpp
@brief 結果実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Result::OnCreate() {
		wstring titleStr = L"";

		//生の値
		ScorePoints score{
			m_data.Time,
			m_data.Crystal,
			m_data.CamNum,
			1
		};
		//かかる倍率
		ScorePoints factor{
			500,	//タイム
			250,	//クリスタル
			100,	//カメラの回転数
			1000,	//クリアボーナス
			1		//トータルスコア
		};
		score = score * factor;

		score.CountTotal(); //初期化の内容から合計を計算

		//タイトルは一つなので別処理
		auto title = GetStage()->AddGameObject<StringSprite2>(L"StageClear");
		title->GetComponent<Transform>()->SetPosition(Vec3(0.0f, 330.0f, 0.0f));

		vector<ResultParam> params{
			{Vec2(-350.0f,70.0f),SpriteType::String,L"Time",1.0f,Align::Horizontal::Left},
			{Vec2(200.0f,70.0f),SpriteType::Number,Util::IntToWStr(m_data.Time),1.0f,Align::Horizontal::Right},
			{Vec2(0.0f,70.0f),SpriteType::Image,L"800,60"},
			{Vec2(230.0f,70.0f),SpriteType::Image,L"320,50"},

			{Vec2(-350.0f,0.0f),SpriteType::String,L"CamRotNum",1.0f,Align::Horizontal::Left},
			{Vec2(300.0f,0.0f),SpriteType::Number,Util::IntToWStr(m_data.CamNum),1.0f,Align::Horizontal::Right},
			{Vec2(0.0f,0.0f),SpriteType::Image,L"800,60"},
			{Vec2(230.0f,0.0f),SpriteType::Image,L"320,50"},

			//{Vec2(-350.0f,-70.0f),SpriteType::String,L"Score",1.0f,Align::Horizontal::Left},
			//{Vec2(300.0f,-120.0f),SpriteType::Number,Util::IntToWStr(score.Total),1.3f,Align::Horizontal::Right},
			//{Vec2(0.0f,-100.0f),SpriteType::Image,L"800,120"},

			//クリスタルとランク
			//{Vec2(-500.0f,140.0f),SpriteType::String,L"Crystal",1.0f,Align::Horizontal::Left},
			//{Vec2(50.0f,140.0f),SpriteType::Number,Util::IntToWStr(m_data.Crystal),1.0f,Align::Horizontal::Right},
			//{Vec2(100.0f,140.0f),SpriteType::String,L"X"},
			//{Vec2(350.0f,140.0f),SpriteType::Number,Util::IntToWStr(factor.Crystal),1.0f,Align::Horizontal::Right},
			//{Vec2(180.0f,80.0f),SpriteType::Image,L"520,50"},
			//{Vec2(420.0f,20.0f),SpriteType::String,L"Rank"}
		};

		Vec2 offset(0.0f, 170.0f);
		for (auto& param : params) {
			param.pos += offset;
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

		Rank rank;
		if (score.Total >= 30000) {
			rank = Rank::S;
		}
		else if (score.Total >= 20000) {
			rank = Rank::A;
		}
		else {
			rank = Rank::B;
		}

		auto uiRank = GetStage()->AddGameObject<UI_Rank>(rank);
		uiRank->SetPosition(Vec2(0.0f, -0.0f));
		uiRank->SetSize(0.9f);
	}

	void Result::CreateString(ResultParam& param) {
		auto str = GetStage()->AddGameObject<StringSprite2>(param.value, param.horizontal, param.vertical);
		auto transComp = str->GetComponent<Transform>();
		transComp->SetPosition((Vec3)param.pos);
		Vec3 scale(m_strSize * param.size);
		transComp->SetScale(scale);
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
			Vec3 scale(m_numSize * param.size);

			auto num = GetStage()->AddGameObject<Numbers>((int)c - '0');
			auto transComp = num->GetComponent<Transform>();
			transComp->SetPosition((Vec3)param.pos + offset);
			transComp->SetScale(scale);
			offset += Vec3(50.0f * key, 0, 0); // 数字の幅の文
		}
	}
}
//end basecross
