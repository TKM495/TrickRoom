/*!
@file Result.cpp
@brief ���ʎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Result::OnCreate() {
		auto stageNum = App::GetApp()->GetScene<Scene>()->GetStageNum();

		auto csvLoad = GetStage()->GetSharedGameObject<CSVLoad>(L"CSVLoad");
		//-1�Ȃ̂�stageNum��1�`�Ȃ̂�
		auto& stageScore = csvLoad->GetStageScoreData()[stageNum - 1];
		wstring titleStr = L"";

		//���̒l
		ScorePoints score{
			m_data.Time,
			m_data.Crystal,
			m_data.CamNum,
			1
		};
		////������{��
		//ScorePoints factor{
		//	500,	//�^�C��
		//	250,	//�N���X�^��
		//	100,	//�J�����̉�]��
		//	1000,	//�N���A�{�[�i�X
		//	1		//�g�[�^���X�R�A
		//};
		//score = score * factor;

		//score.CountTotal(); //�������̓��e���獇�v���v�Z
		auto stage = GetStage();
		auto back = stage->AddGameObject<PictureFrame>(Vec2(1100.0f, 640.0f), false);
		back->SetPos(Vec2(0.0f, 120.0f));

		//�^�C�g���͈�Ȃ̂ŕʏ���
		auto title = stage->AddGameObject<StringSprite2>(L"StageClear");
		title->GetComponent<Transform>()->SetPosition(Vec3(0.0f, 320.0f, 0.0f));

		vector<ResultParam> params{
			{Vec2(-350.0f,70.0f),SpriteType::String,L"Time",1.0f,Align::Horizontal::Left},
			{Vec2(300.0f,70.0f),SpriteType::Number,Util::IntToWStr(m_data.Time),1.0f,Align::Horizontal::Right},
			{Vec2(0.0f,70.0f),SpriteType::Image,L"800,60"},
			{Vec2(230.0f,70.0f),SpriteType::Image,L"320,50"},

			{Vec2(-350.0f,0.0f),SpriteType::String,L"CamRotNum",1.0f,Align::Horizontal::Left},
			{Vec2(300.0f,0.0f),SpriteType::Number,Util::IntToWStr(m_data.CamNum),1.0f,Align::Horizontal::Right},
			{Vec2(360.0f,0.0f),SpriteType::String,L"Count",1.0f,Align::Horizontal::Right},
			{Vec2(0.0f,0.0f),SpriteType::Image,L"800,60"},
			{Vec2(230.0f,0.0f),SpriteType::Image,L"320,50"},
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
		if (score.Time <= stageScore.Time[0] &&
			score.CamNum <= stageScore.CamNum[0]) {
			rank = Rank::S;
		}
		else if (score.Time <= stageScore.Time[1] &&
			score.CamNum <= stageScore.CamNum[1]) {
			rank = Rank::A;
		}
		else {
			rank = Rank::B;
		}

		auto uiRank = GetStage()->AddGameObject<UI_Rank>(rank);
		uiRank->SetPosition(Vec2(0.0f, -0.0f));
		uiRank->SetSize(0.8f);
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
			offset += Vec3(40.0f * key, 0, 0); // �����̕��̕�
		}
	}
}
//end basecross
