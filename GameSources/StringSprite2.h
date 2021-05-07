/*!
@file StringSprite2.h
@brief 文字列表示用クラス
*/

#pragma once
#include "stdafx.h"
#include "CSVLoad.h"
#include "FadeComponent.h"

namespace basecross {
	//揃え方
	struct Align {
		//垂直方向
		enum class Vertical {
			Top,
			Center,
			Bottom
		};
		//水平方向
		enum class Horizontal {
			Left,
			Center,
			Right
		};
	};

	class StringSprite2 :public GameObject {
		//時間計測用
		float m_delta;
		//非アクティブになるまでの時間
		float m_deActiveTime;
		//非アクティブかどうか
		bool m_bDeactive;
		//色
		Col4 m_color;
		//自分のデータ
		SpriteDataFormat m_data;
		//表示する文字の名前
		wstring m_name;
		//横の設定
		Align::Horizontal m_horizontal;
		//縦の設定
		Align::Vertical m_vertical;
		//頂点データ
		vector<VertexPositionColorTexture> vertices;
		//輪郭用の自分自身のコピー
		shared_ptr<StringSprite2> m_outlineObj;
	public:
		StringSprite2(const shared_ptr<Stage>& stage,
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

		//各種配置設定関数
		void SetAlignHorizontal(Align::Horizontal hor);
		void SetAlignVertical(Align::Vertical ver);

		void SetSize(float size);
		void SetPos(Vec2 pos);
		float GetSize();
		Vec3 GetPos();
		Vec2 GetTexSize() {
			return m_data.size;
		}

		shared_ptr<FadeComponent> GetFadeComp() {
			return GetComponent<FadeComponent>();
		}

		void SetColor(Col4 color);
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
