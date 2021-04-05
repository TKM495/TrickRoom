/*!
@file Dot1x1.cpp
@brief 1x1のドット実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Dot1x1::OnCreate() {
		auto size = m_data.size;
		Rect2D<float> pos;
		//縦位置の設定
		switch (m_data.horizontal)
		{
		case basecross::Align::Horizontal::Left:
			pos.left = 0.0f;
			pos.right = size.x;
			break;
		case basecross::Align::Horizontal::Center:
			pos.left = size.x / 2.0f;
			pos.right = size.x / 2.0f;
			break;
		case basecross::Align::Horizontal::Right:
			pos.left = size.x;
			pos.right = 0.0f;
			break;
		default:
			//エラー
			break;
		}
		//横位置の設定
		switch (m_data.vertical)
		{
		case basecross::Align::Vertical::Top:
			pos.top = 0.0f;
			pos.bottom = size.y;
			break;
		case basecross::Align::Vertical::Center:
			pos.top = size.y / 2.0f;
			pos.bottom = size.y / 2.0f;
			break;
		case basecross::Align::Vertical::Bottom:
			pos.top = size.y;
			pos.bottom = 0.0f;
			break;
		default:
			//エラー
			break;
		}
		//頂点のデータ (番号は左上から右下まで)
		vertices = {
			{Vec3(-pos.left,+pos.top,0.0f),m_data.color,Vec2(0.0f)}, //0
			{Vec3(+pos.right,+pos.top,0.0f),m_data.color,Vec2(0.0f)}, //1

			{Vec3(-pos.left,-pos.bottom,0.0f),m_data.color,Vec2(0.0f)}, //2
			{Vec3(+pos.right,-pos.bottom,0.0f),m_data.color,Vec2(0.0f)},  //3
		};
		//頂点インデックス
		vector<uint16_t> indices = {
			0, 1, 2, //上の三角形
			2, 1, 3 //下の三角形
		};

		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);
		drawComp->SetTextureResource(L"white");
		drawComp->SetSamplerState(SamplerState::AnisotropicWrap); //テクスチャの繰り返し設定(Wrap)
		drawComp->SetDepthStencilState(DepthStencilState::Read);

		SetAlphaActive(true); //透明をサポートする&両面描画になる

		GetComponent<Transform>()->SetPosition((Vec3)m_data.position);
	}

	void Dot1x1::SetAlignHorizontal(Align::Horizontal hor) {
		auto size = m_data.size;
		m_data.horizontal = hor;
		Rect2D<float> pos;
		//縦位置の設定
		switch (m_data.horizontal)
		{
		case basecross::Align::Horizontal::Left:
			pos.left = 0.0f;
			pos.right = size.x;
			break;
		case basecross::Align::Horizontal::Center:
			pos.left = size.x / 2.0f;
			pos.right = size.x / 2.0f;
			break;
		case basecross::Align::Horizontal::Right:
			pos.left = size.x;
			pos.right = 0.0f;
			break;
		default:
			//エラー
			break;
		}
		vertices[0].position.x = vertices[2].position.x = -pos.left;
		vertices[1].position.x = vertices[3].position.x = +pos.right;
		GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
	}

	void Dot1x1::SetAlignVertical(Align::Vertical ver) {
		auto size = m_data.size;
		m_data.vertical = ver;
		Rect2D<float> pos;
		//横位置の設定
		switch (m_data.vertical)
		{
		case basecross::Align::Vertical::Top:
			pos.top = 0.0f;
			pos.bottom = size.y;
			break;
		case basecross::Align::Vertical::Center:
			pos.top = size.y / 2.0f;
			pos.bottom = size.y / 2.0f;
			break;
		case basecross::Align::Vertical::Bottom:
			pos.top = size.y;
			pos.bottom = 0.0f;
			break;
		default:
			//エラー
			break;
		}
		vertices[0].position.y = vertices[1].position.y = +pos.top;
		vertices[2].position.y = vertices[3].position.y = -pos.bottom;
		GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
	}

	void Dot1x1::SetSize(Vec2 size) {
		auto origin = m_data.position;
		m_data.size = size;
		Rect2D<float> pos;
		//縦位置の設定
		switch (m_data.horizontal)
		{
		case basecross::Align::Horizontal::Left:
			pos.left = 0.0f;
			pos.right = m_data.size.x;
			break;
		case basecross::Align::Horizontal::Center:
			pos.left = m_data.size.x / 2.0f;
			pos.right = m_data.size.x / 2.0f;
			break;
		case basecross::Align::Horizontal::Right:
			pos.left = m_data.size.x;
			pos.right = 0.0f;
			break;
		default:
			//エラー
			break;
		}
		//横位置の設定
		switch (m_data.vertical)
		{
		case basecross::Align::Vertical::Top:
			pos.top = 0.0f;
			pos.bottom = m_data.size.y;
			break;
		case basecross::Align::Vertical::Center:
			pos.top = m_data.size.y / 2.0f;
			pos.bottom = m_data.size.y / 2.0f;
			break;
		case basecross::Align::Vertical::Bottom:
			pos.top = m_data.size.y;
			pos.bottom = 0.0f;
			break;
		default:
			//エラー
			break;
		}

		vertices[0].position = Vec3( -pos.left,    +pos.top, 0.0f);
		vertices[1].position = Vec3(+pos.right,    +pos.top, 0.0f);
		vertices[2].position = Vec3( -pos.left, -pos.bottom, 0.0f);
		vertices[3].position = Vec3(+pos.right, -pos.bottom, 0.0f);

		GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
	}
}
//end basecross
