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
		GameStage::GameState state;	//�Q�[���̏��
		int HP;						//HP
		int RCrystal;				//�ԐF�̃N���X�^��
		int BCrystal;				//�F�̃N���X�^��
		int Distance;				//�X�^�[�g����̋���
	};

	struct ScorePoints {
		int HP;			//HP
		int RCrystal;	//�ԐF�̃N���X�^��
		int BCrystal;	//�F�̃N���X�^��
		int Distance;	//�X�^�[�g����̋���
		int ClearBonus;	//�N���A�{�[�i�X
		int Total;		//���v
		void CountTotal() {
			Total = HP + RCrystal + BCrystal + Distance + ClearBonus;
		}

		ScorePoints operator*(const ScorePoints& _score)const {
			ScorePoints score;
			score.HP = this->HP * _score.HP;
			score.RCrystal = this->RCrystal * _score.RCrystal;
			score.BCrystal = this->BCrystal * _score.BCrystal;
			score.Distance = this->Distance * _score.Distance;
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
