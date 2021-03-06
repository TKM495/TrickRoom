/*!
@file ImageSprite.cpp
@brief 画像表示用クラスの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void ImageSprite::OnCreate() {
		auto origin = Vec2(0.0f);
		auto size = Utility::GetTextureSize(m_name);
		Rect2D<float> pos;
		//縦位置の設定
		switch (m_horizontal)
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
		switch (m_vertical)
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
		vector<Vec2> uvs,uv = {
			origin,
			origin + Vec2(size.x,0.0f),
			origin + Vec2(0.0f, size.y),
			origin + size
		};
		Utility::ConvertToUVCoordinates(uv, size, uvs);
		//頂点のデータ
		vertices = {
			{Vec3(-pos.left,+pos.top,0.0f),m_color,uvs[0]}, //0
			{Vec3(+pos.right,+pos.top,0.0f),m_color,uvs[1]}, //1

			{Vec3(-pos.left,-pos.bottom,0.0f),m_color,uvs[2]}, //2
			{Vec3(+pos.right,-pos.bottom,0.0f),m_color,uvs[3]},  //3
		};
		//頂点インデックス
		vector<uint16_t> indices = {
			0, 1, 2, //上の三角形
			2, 1, 3 //下の三角形
		};

		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);
		drawComp->SetTextureResource(m_name);
		drawComp->SetSamplerState(SamplerState::AnisotropicWrap); //テクスチャの繰り返し設定(Wrap)
		drawComp->SetDepthStencilState(DepthStencilState::Read);

		auto fade = AddComponent<FadeComponent>();
		fade->SetFadeColor(m_color);

		SetAlphaActive(true); //透明をサポートする&両面描画になる
		//GetComponent<Transform>()->SetScale(Vec3(0.005f));

		SetUpdateActive(false);
	}

	void ImageSprite::OnUpdate() {
		auto delta = App::GetApp()->GetElapsedTime();
		auto fade = GetComponent<FadeComponent>();
		if (m_delta > m_deActiveTime && !m_bDeactive) {
			fade->FadeOut();
			m_bDeactive = true;
		}

		if (!fade->IsFadeActive() && m_bDeactive) {
			m_delta = 0.0f;
			m_bDeactive = false;
			SetDrawActive(false);
			SetUpdateActive(false);
		}
		m_delta += delta;
	}


	void ImageSprite::SetAlignHorizontal(Align::Horizontal hor) {
		auto origin = Vec2(0.0f);
		auto size = Utility::GetTextureSize(m_name);
		m_horizontal = hor;
		Rect2D<float> pos;
		//縦位置の設定
		switch (m_horizontal)
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

	void ImageSprite::SetAlignVertical(Align::Vertical ver) {
		auto origin = Vec2(0.0f);
		auto size = Utility::GetTextureSize(m_name);
		m_vertical = ver;
		Rect2D<float> pos;
		//横位置の設定
		switch (m_vertical)
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

	void ImageSprite::SetSize(float size) {
		GetComponent<Transform>()->SetScale(Vec3(size));
	}

	void ImageSprite::SetPos(Vec2 pos) {
		GetComponent<Transform>()->SetPosition((Vec3)pos);
	}

	void ImageSprite::SetRot(float rot) {
		GetComponent<Transform>()->SetRotation(0.0f, 0.0f, XMConvertToRadians(rot));
	}

	float ImageSprite::GetRot() {
		//大きさは同じなのでとりあえずxを返す
		return GetComponent<Transform>()->GetRotation().z;
	}

	float ImageSprite::GetSize() {
		//大きさは同じなのでとりあえずxを返す
		return GetComponent<Transform>()->GetScale().x;
	}

	Vec3 ImageSprite::GetPos() {
		return GetComponent<Transform>()->GetPosition();
	}
}
//end basecross
