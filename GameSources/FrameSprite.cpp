/*!
@file FrameSprite.cpp
@brief 背景画像実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void FrameSprite::OnCreate() {
		//CSVLoadを取得しデータをもらう
		auto csvLoad = dynamic_pointer_cast<CSVLoad>(GetStage()->GetSharedObject(L"CSVLoad"));
		auto& data = csvLoad->GetImageSpriteData();
		//目標のデータを探す
		int index = Utility::SearchDataIndex(data, L"Background");
		if (index == -1) {
			throw BaseException(
				L"目標のデータが見つかりません",
				L"name : Background",
				L"FrameSprite::OnCreate()"
			);
		}
		auto dat = data[index];
		m_baseSize = dat.size;
		if (m_baseSize.x > m_size.x || m_baseSize.y > m_size.y) {
			throw BaseException(
				L"指定されたサイズが最小のサイズより小さいです",
				L"BaseSize > Size",
				L"FrameSprite::OnCreate()"
			);
		}

		auto baseSizeHalf = m_baseSize / 2.0f;
		auto origin = dat.origin;
		auto pos = SetAlignPosition(m_horizontal, m_vertical, m_size);
		//頂点のデータ (番号は左上から右下まで)
		vertices = {
			{Vec3(-pos.left                  ,   pos.top       ,0.0f) ,   m_color,(origin)/512.0f},  //0
			{Vec3(-pos.left + baseSizeHalf.x ,   pos.top       ,0.0f) ,m_color,(origin+Vec2(baseSizeHalf.x,0.0f))/512.0f},  //1
			{Vec3(-pos.left                  ,+pos.top -baseSizeHalf.y  ,0.0f),m_color,(origin + Vec2(0.0f,baseSizeHalf.y)) / 512.0f},  //2
			{Vec3(-pos.left + baseSizeHalf.x ,+pos.top -baseSizeHalf.y  ,0.0f),m_color,(origin + baseSizeHalf) / 512.0f},  //3

			{Vec3(+pos.right - baseSizeHalf.x ,   +pos.top      ,0.0f),   m_color,(origin+Vec2(baseSizeHalf.x,0.0f))/512.0f},  //4
			{Vec3(+pos.right                  ,   +pos.top      ,0.0f),m_color,(origin+Vec2(m_baseSize.x,0.0f))/512.0f},  //5
			{Vec3(+pos.right - baseSizeHalf.x ,+pos.top -baseSizeHalf.y  ,0.0f),m_color,(origin + baseSizeHalf) / 512.0f},  //6
			{Vec3(+pos.right                  ,+pos.top -baseSizeHalf.y  ,0.0f),m_color,(origin + Vec2(m_baseSize.x,baseSizeHalf.y)) / 512.0f},  //7

			{Vec3(-pos.left                  ,   -pos.bottom+baseSizeHalf.y,0.0f),   m_color,(origin+Vec2(0.0f,baseSizeHalf.y))/512.0f},  //8
			{Vec3(-pos.left + baseSizeHalf.x ,-pos.bottom +baseSizeHalf.y   ,0.0f),m_color,(origin+ baseSizeHalf)/512.0f},  //9
			{Vec3(-pos.left                  ,-pos.bottom         ,0.0f)  ,m_color,(origin + Vec2(0.0f,m_baseSize.y)) / 512.0f},  //10
			{Vec3(-pos.left + baseSizeHalf.x ,-pos.bottom         ,0.0f)  ,m_color,(origin + Vec2(baseSizeHalf.x,m_baseSize.y)) / 512.0f},  //11

			{Vec3(+pos.right -baseSizeHalf.x  ,-pos.bottom +baseSizeHalf.y   ,0.0f),   m_color,(origin+baseSizeHalf)/512.0f},  //12
			{Vec3(+pos.right                  ,   -pos.bottom +baseSizeHalf.y,0.0f),m_color,(origin+ Vec2(m_baseSize.x,baseSizeHalf.y))/512.0f},  //13
			{Vec3(+pos.right -baseSizeHalf.x  ,-pos.bottom         ,0.0f)   ,m_color,(origin + Vec2(baseSizeHalf.x,m_baseSize.y)) / 512.0f},  //14
			{Vec3(+pos.right                  ,-pos.bottom         ,0.0f)   ,m_color,(origin + m_baseSize) / 512.0f},  //15

		    };
		//頂点インデックス
		vector<uint16_t> indices = {
			0,1,2,
			2,1,3,
			4,5,6,
			6,5,7,
			8,9,10,
			10,9,11,
			12,13,14,
			14,13,15,

			1,4,3,
			3,4,6,
			6,7,12,
			12,7,13,
			9,12,11,
			11,12,14,
			2,3,8,
			8,3,9,

			3,6,9,
			9,6,12
		};

		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);
		drawComp->SetTextureResource(L"Sprite");
		drawComp->SetSamplerState(SamplerState::AnisotropicWrap); //テクスチャの繰り返し設定(Wrap)
		drawComp->SetDepthStencilState(DepthStencilState::Read);

		SetAlphaActive(true); //透明をサポートする&両面描画になる
	}

	//void FrameSprite::SetAlignVertical(Align::Vertical ver) {
	//	auto size = m_data.size;
	//	m_data.vertical = ver;
	//	Rect2D<float> pos;
	//	//横位置の設定
	//	switch (m_data.vertical)
	//	{
	//	case basecross::Align::Vertical::Top:
	//		pos.top = 0.0f;
	//		pos.bottom = size.y;
	//		break;
	//	case basecross::Align::Vertical::Center:
	//		pos.top = size.y / 2.0f;
	//		pos.bottom = size.y / 2.0f;
	//		break;
	//	case basecross::Align::Vertical::Bottom:
	//		pos.top = size.y;
	//		pos.bottom = 0.0f;
	//		break;
	//	default:
	//		//エラー
	//		break;
	//	}
	//	vertices[0].position.y = vertices[1].position.y = +pos.top;
	//	vertices[2].position.y = vertices[3].position.y = -pos.bottom;
	//	GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
	//}

	//void FrameSprite::SetSize(Vec2 size) {
	//	auto origin = m_data.position;
	//	m_data.size = size;
	//	Rect2D<float> pos;
	//	//縦位置の設定
	//	switch (m_data.horizontal)
	//	{
	//	case basecross::Align::Horizontal::Left:
	//		pos.left = 0.0f;
	//		pos.right = m_data.size.x;
	//		break;
	//	case basecross::Align::Horizontal::Center:
	//		pos.left = m_data.size.x / 2.0f;
	//		pos.right = m_data.size.x / 2.0f;
	//		break;
	//	case basecross::Align::Horizontal::Right:
	//		pos.left = m_data.size.x;
	//		pos.right = 0.0f;
	//		break;
	//	default:
	//		//エラー
	//		break;
	//	}
	//	//横位置の設定
	//	switch (m_data.vertical)
	//	{
	//	case basecross::Align::Vertical::Top:
	//		pos.top = 0.0f;
	//		pos.bottom = m_data.size.y;
	//		break;
	//	case basecross::Align::Vertical::Center:
	//		pos.top = m_data.size.y / 2.0f;
	//		pos.bottom = m_data.size.y / 2.0f;
	//		break;
	//	case basecross::Align::Vertical::Bottom:
	//		pos.top = m_data.size.y;
	//		pos.bottom = 0.0f;
	//		break;
	//	default:
	//		//エラー
	//		break;
	//	}

	//	vertices[0].position = Vec3(-pos.left, +pos.top, 0.0f);
	//	vertices[1].position = Vec3(+pos.right, +pos.top, 0.0f);
	//	vertices[2].position = Vec3(-pos.left, -pos.bottom, 0.0f);
	//	vertices[3].position = Vec3(+pos.right, -pos.bottom, 0.0f);

	//	GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
	//}

	Rect2D<float> FrameSprite::SetAlignPosition(Align::Horizontal hor, Align::Vertical ver, const Vec2& size) {
		Rect2D<float> pos;
		//縦位置の設定
		switch (hor)
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
		switch (ver)
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
		return pos;
	}

	void FrameSprite::SetSize(Vec2 size) {
		GetComponent<Transform>()->SetScale((Vec3)size);
	}

	void FrameSprite::SetPosition(Vec2 pos) {
		GetComponent<Transform>()->SetPosition((Vec3)pos);
	}

	void FrameSprite::SetColor(Col4 color) {
		GetComponent<PCTSpriteDraw>()->SetDiffuse(color);
	}
}
//end basecross
