/*!
@file Result.h
@brief ����
*/

#pragma once
#include "stdafx.h"
#include "StringSprite2.h"
#include "GameStage.h"

namespace basecross {
	//�X�R�A�ɕK�v�ȃf�[�^
	struct ScoreData {
		GameStage::GameState state;	//�Q�[���̏��
		int HP;						//HP
		int RCrystal;				//�ԐF�̃N���X�^��
		int BCrystal;				//�F�̃N���X�^��
		int Distance;				//�X�^�[�g����̋���
	};

	enum class SpriteType {
		String,
		Image,
		Number
	};

	struct ResultParam {
		Vec2 pos;
		SpriteType type;
		wstring value;
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
			m_numSize(0.7f)
		{}

		virtual void OnCreate()override;

		void CreateString(ResultParam& param);
		void CreateImage(ResultParam& param);
		void CreateNumber(ResultParam& param);
	};

}
//end basecross
