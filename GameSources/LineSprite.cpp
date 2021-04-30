/*!
@file LineSprite.cpp
@brief ラインスプライトの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void LineSprite::SetPosition(Vec2 pos) {
		GetComponent<Transform>()->SetPosition((Vec3)pos);
	}
	void LineSprite::SetRotation(float rot) {
		GetComponent<Transform>()->SetRotation(Vec3(0.0f, 0.0f, XMConvertToRadians(rot)));
	}
	void LineSprite::SetLength(float length) {
		m_length = length;
		GetComponent<Transform>()->SetScale(Vec3(m_length, m_thickness, 1.0f));
	}
	void LineSprite::SetThickness(float thickness) {
		m_thickness = thickness;
		GetComponent<Transform>()->SetScale(Vec3(m_length, m_thickness, 1.0f));
	}
	void LineSprite::SetStatus(float length, float thickness, Col4 color) {
		SetLength(length);
		SetThickness(thickness);
		SetColor(color);
	}
	void LineSprite::SetStatus(float length, float thickness) {
		SetLength(length);
		SetThickness(thickness);
	}
	void LineSprite::SetColor(Col4 color) {
		GetComponent<PCSpriteDraw>()->SetDiffuse(color);
	}

	Vec2 LineSprite::GetPosition(){
		return (Vec2)GetComponent<Transform>()->GetPosition();
	}
	float LineSprite::GetRotation(){
		return GetComponent<Transform>()->GetRotation().z;
	}
	float LineSprite::GetLength() { return m_length; }
	float LineSprite::GetThickness() { return m_thickness; }
	Col4 LineSprite::GetColor() { return m_color; }

	void LineSprite::OnCreate() {
		Rect2D<float> pos;
		pos.top = +0.5f;
		pos.bottom = -0.5f;
		switch (m_horizontal)
		{
		case Align::Horizontal::Left:
			pos.left = 0.0f;
			pos.right = +1.0f;
			break;
		case Align::Horizontal::Center:
			pos.left = -0.5f;
			pos.right = +0.5f;
			break;
		case Align::Horizontal::Right:
			pos.left = -1.0f;
			pos.right = 0.0f;
			break;
		default:
			//エラー
			break;
		}
		Col4 color(1.0f);
		vector<VertexPositionColor> vertices = {
			{Vec3(pos.left ,pos.top   ,0.0f),color}, //0
			{Vec3(pos.right,pos.top   ,0.0f),color}, //1
			{Vec3(pos.left ,pos.bottom,0.0f),color}, //2
			{Vec3(pos.right,pos.bottom,0.0f),color},  //3
		};
		//頂点インデックス(頂点をつなげる順番)
		std::vector<uint16_t> indices = {
			0, 1, 2, //上の三角形
			2, 1, 3  //下の三角形
		};
		auto drawComp = AddComponent<PCSpriteDraw>(vertices, indices);
		drawComp->SetDiffuse(m_color);
	}
}
//end basecross