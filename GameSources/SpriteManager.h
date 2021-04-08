///*!
//@file SpriteManager.h
//@brief スプライト管理クラス
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
//		//スプライトタイプ
//		SpriteType m_type;
//		//オブジェクトを格納する配列(0:本体,1:アウトライン用)
//		shared_ptr<GameObject> m_objs[2];
//		//色
//		Col4 m_colors[2];
//		//データ(数値で渡すものもあるが文字列でもらう)
//		wstring m_value;
//		//大きさ
//		float m_size;
//		//アウトラインをどうするか
//		bool m_bOutline;
//		//アウトラインのサイズ
//		float m_outlineSize;
//		//横の設定
//		Align::Horizontal m_horizontal;
//		//縦の設定
//		Align::Vertical m_vertical;
//		//アウトラインの作成
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
//		//各種配置設定関数
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
