///*!
//@file SpriteManager.h
//@brief �X�v���C�g�Ǘ��N���X
//*/
//
//#pragma once
//#include "stdafx.h"
//#include "StringSprite2.h"
//
//namespace basecross {
//	enum class SpriteType {
//		String,
//		Image,
//		Number
//	};
//
//	class SpriteManager :public GameObject {
//		//�X�v���C�g�^�C�v
//		SpriteType m_type;
//		//�I�u�W�F�N�g���i�[����z��(0:�{��,1:�A�E�g���C���p)
//		shared_ptr<GameObject> m_objs[2];
//		//�F
//		Col4 m_colors[2];
//		//�f�[�^(���l�œn�����̂����邪������ł��炤)
//		wstring m_value;
//		//�傫��
//		float m_size;
//		//�A�E�g���C�����ǂ����邩
//		bool m_bOutline;
//		//�A�E�g���C���̃T�C�Y
//		float m_outlineSize;
//		//���̐ݒ�
//		Align::Horizontal m_horizontal;
//		//�c�̐ݒ�
//		Align::Vertical m_vertical;
//		//�A�E�g���C���̍쐬
//		void CreateOutline();
//	public:
//		SpriteManager(const shared_ptr<Stage>& stage,
//			SpriteType type,
//			const wstring& value)
//			:GameObject(stage),
//			m_type(type),
//			m_value(value),
//			m_horizontal(Align::Horizontal::Center),
//			m_vertical(Align::Vertical::Center),
//			m_bOutline(false),
//			m_outlineSize(0.01),
//			m_size(1.0f)
//		{
//			m_colors[0] = Col4(0.0f, 0.0f, 1.0f, 1.0f);
//			m_colors[1] = Col4(1.0f, 1.0f, 1.0f, 1.0f);
//		}
//
//		virtual void OnCreate()override;
//
//		//�e��z�u�ݒ�֐�
//		void SetAlignHorizontal(Align::Horizontal hor);
//		void SetAlignVertical(Align::Vertical ver);
//		void IsOutline(bool flg);
//		void SetOutlineSize(float size) {
//			m_outlineSize = size;
//		}
//		void SetColor(int num, Col4 color);
//
//		void SetSize(float size);
//		void SetPos(Vec3 pos);
//		float GetSize();
//		Vec3 GetPos();
//
//		void SetDrawSprite(bool flg);
//	};
//
//}
////end basecross
