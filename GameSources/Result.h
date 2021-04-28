/*!
@file Result.h
@brief ����
*/

#pragma once
#include "stdafx.h"
#include "StringSprite2.h"
#include "GameStage.h"
#include "SpriteManager.h"

namespace basecross {
	//�X�R�A�ɕK�v�ȃf�[�^
	struct ScoreData {
		float Time;					//�^�C��
		int Crystal;				//�N���X�^��
		int CamNum;					//�J�����̉�]��
	};

	struct ScorePoints {
		float Time;		//�^�C��
		int Crystal;	//�N���X�^��
		int CamNum;		//�J�����̉�]��
		int ClearBonus;	//�N���A�{�[�i�X
		int Total;		//���v
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
		Align::Horizontal horizontal = Align::Horizontal::Center;	//���������ʒu
		Align::Vertical vertical = Align::Vertical::Center;		//���������ʒu
	};

	//struct ResultElement {
	//	Vec2 pos;						//�ʒu
	//	vector<ResultParam> elements;	//�e�v�f
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
