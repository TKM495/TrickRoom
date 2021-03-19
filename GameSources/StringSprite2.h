/*!
@file StringSprite2.h
@brief ������\���p�N���X
*/

#pragma once
#include "stdafx.h"
#include "CSVLoad.h"

namespace basecross {
	//������
	struct Align {
		//��������
		enum class Vertical {
			Top,
			Center,
			Bottom
		};
		//��������
		enum class Horizontal {
			Left,
			Center,
			Right
		};
	};

	class StringSprite2 :public GameObject {
		//�����̃f�[�^
		SpriteDataFormat m_data;
		//�\�����镶���̖��O
		wstring m_name;
		//���̐ݒ�
		Align::Horizontal m_horizontal;
		//�c�̐ݒ�
		Align::Vertical m_vertical;
		//���_�f�[�^
		vector<VertexPositionColorTexture> vertices;
		//�f�[�^�̒�����m_name�Ɉ�v����f�[�^��Ԃ��֐�
		int SearchDataIndex(vector<SpriteDataFormat>& data);
	public:
		StringSprite2(const shared_ptr<Stage>& stage,
			wstring name,
			Align::Horizontal horizontal = Align::Horizontal::Center,
			Align::Vertical vertical = Align::Vertical::Center)
			:GameObject(stage),
			m_name(name),
			m_horizontal(horizontal),
			m_vertical(vertical)
		{}

		virtual void OnCreate()override;

		//�e��z�u�ݒ�֐�
		void SetAlignHorizontal(Align::Horizontal hor);
		void SetAlignVertical(Align::Vertical ver);
	};

}
//end basecross
