/*!
@file Result.h
@brief 結果
*/

#pragma once
#include "stdafx.h"
#include "StringSprite2.h"
#include "GameStage.h"
#include "SpriteManager.h"

namespace basecross {
	//スコアに必要なデータ
	struct ScoreData {
		float Time;					//タイム
		int Crystal;				//クリスタル
		int CamNum;					//カメラの回転数
	};

	struct ScorePoints {
		float Time;		//タイム
		int Crystal;	//クリスタル
		int CamNum;		//カメラの回転数
		int ClearBonus;	//クリアボーナス
		int Total;		//合計
		void CountTotal() {
			Total = Time + Crystal + CamNum + ClearBonus;
		}

		ScorePoints operator*(const ScorePoints& _score)const {
			ScorePoints score;
			score.Time = this->Time * _score.Time;
			score.Crystal = this->Crystal * _score.Crystal;
			score.CamNum = this->CamNum * _score.CamNum;
			score.ClearBonus = this->ClearBonus * _score.ClearBonus;
			score.Total = this->Total * _score.Total;
			return score;
		}
	};

	struct ResultParam {
		Vec2 pos;
		SpriteType type;
		wstring value;
		float size = 1.0f;
		Align::Horizontal horizontal = Align::Horizontal::Center;	//水平揃え位置
		Align::Vertical vertical = Align::Vertical::Center;		//垂直揃え位置
	};

	//struct ResultElement {
	//	Vec2 pos;						//位置
	//	vector<ResultParam> elements;	//各要素
	//};

	class Result :public GameObject {
		ScoreData m_data;
		float m_strSize;
		float m_numSize;
	public:
		Result(const shared_ptr<Stage>& stage,
			const ScoreData& data)
			:GameObject(stage),
			m_data(data),
			m_strSize(0.8f),
			m_numSize(0.5f)
		{}

		virtual void OnCreate()override;

		void CreateString(ResultParam& param);
		void CreateImage(ResultParam& param);
		void CreateNumber(ResultParam& param);
	};

}
//end basecross
