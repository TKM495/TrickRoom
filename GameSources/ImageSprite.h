/*!
@file ImageSprite.h
@brief ������\���p�N���X
*/

#pragma once
#include "stdafx.h"
#include "CSVLoad.h"
#include "FadeComponent.h"
#include "StringSprite2.h"

namespace basecross {
	class ImageSprite :public GameObject {
		//���Ԍv���p
		float m_delta;
		//��A�N�e�B�u�ɂȂ�܂ł̎���
		float m_deActiveTime;
		//��A�N�e�B�u���ǂ���
		bool m_bDeactive;
		//�F
		Col4 m_color;
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
		//�֊s�p�̎������g�̃R�s�[
		shared_ptr<StringSprite2> m_outlineObj;
		//�f�[�^�̒�����m_name�Ɉ�v����f�[�^��Ԃ��֐�
		int SearchDataIndex(vector<SpriteDataFormat>& data);
	public:
		ImageSprite(const shared_ptr<Stage>& stage,
			wstring name,
			Align::Horizontal horizontal = Align::Horizontal::Center,
			Align::Vertical vertical = Align::Vertical::Center,
			Col4 color = Col4(0.0f, 0.0f, 0.0f, 1.0f))
			:GameObject(stage),
			m_name(name),
			m_horizontal(horizontal),
			m_vertical(vertical),
			m_color(color),
			m_delta(0.0f),
			m_bDeactive(false)
		{}

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		//�e��z�u�ݒ�֐�
		void SetAlignHorizontal(Align::Horizontal hor);
		void SetAlignVertical(Align::Vertical ver);

		void SetSize(float size);
		void SetPos(Vec3 pos);
		void SetRot(float rot);
		float GetRot();
		float GetSize();
		Vec3 GetPos();

		shared_ptr<FadeComponent> GetFadeComp() {
			return GetComponent<FadeComponent>();
		}

		Col4 GetColor() {
			return m_color;
		}

		void Deactive(float time) {
			m_deActiveTime = time;
			SetUpdateActive(true);
		}
		void Deactive() {
			Deactive(0.0f);
		}
	};

}
//end basecross