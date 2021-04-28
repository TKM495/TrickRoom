/*!
@file FrameSprite.cpp
@brief 背景画像実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void FrameSprite::OnCreate() {
		auto size = Utility::GetTextureSize(L"Frame");
		auto baseSize = size / 2.0f;
		if (baseSize.x > m_size.x || baseSize.y > m_size.y) {
			throw BaseException(
				L"指定されたサイズが最小のサイズより小さいです",
				L"BaseSize > Size",
				L"FrameSprite::OnCreate()"
			);
		}

		Rect2D<float> pos;

		pos.left = (m_size.x / 2.0f);
		pos.right = (m_size.x / 2.0f);
		pos.top = (m_size.y / 2.0f);
		pos.bottom = (m_size.y / 2.0f);
		auto origin = Vec2(0.0f);
		auto baseSizeHalf = size / 2.0f;
		vector<Vec2> uvs, uv = {
			origin,
			origin + Vec2(baseSizeHalf.x, 0.0f),
			origin + Vec2(0.0f, baseSizeHalf.y),
			origin + baseSizeHalf,

			origin + Vec2(baseSizeHalf.x, 0.0f),
			origin + Vec2(size.x, 0.0f),
			origin + baseSizeHalf,
			origin + Vec2(size.x, baseSizeHalf.y),

			origin + Vec2(0.0f, baseSizeHalf.y),
			origin + baseSizeHalf,
			origin + Vec2(0.0f, size.y),
			origin + Vec2(baseSizeHalf.x, size.y),

			origin + baseSizeHalf,
			origin + Vec2(size.x, baseSizeHalf.y),
			origin + Vec2(baseSizeHalf.x, size.y),
			origin + size,
		};
		Utility::ConvertToUVCoordinates(uv, size, uvs);
		Col4 color(1.0f);
		//頂点のデータ (番号は左上から右下まで)
		vertices = {
			{Vec3(-pos.left                  ,+pos.top                 ,0.0f),color,uvs[0]},  //0
			{Vec3(-pos.left + baseSizeHalf.x ,+pos.top                 ,0.0f),color,uvs[1]},  //1
			{Vec3(-pos.left                  ,+pos.top - baseSizeHalf.y,0.0f),color,uvs[2]},  //2
			{Vec3(-pos.left + baseSizeHalf.x ,+pos.top - baseSizeHalf.y,0.0f),color,uvs[3]},  //3

			{Vec3(+pos.right - baseSizeHalf.x,+pos.top                 ,0.0f),color,uvs[4]},  //4
			{Vec3(+pos.right                 ,+pos.top                 ,0.0f),color,uvs[5]},  //5
			{Vec3(+pos.right - baseSizeHalf.x,+pos.top - baseSizeHalf.y,0.0f),color,uvs[6]},  //6
			{Vec3(+pos.right                 ,+pos.top - baseSizeHalf.y,0.0f),color,uvs[7]},  //7

			{Vec3(-pos.left                  ,-pos.bottom + baseSizeHalf.y,0.0f),color,uvs[8]},  //8
			{Vec3(-pos.left + baseSizeHalf.x ,-pos.bottom + baseSizeHalf.y,0.0f),color,uvs[9]},  //9
			{Vec3(-pos.left                  ,-pos.bottom                 ,0.0f),color,uvs[10]},  //10
			{Vec3(-pos.left + baseSizeHalf.x ,-pos.bottom                 ,0.0f),color,uvs[11]},  //11

			{Vec3(+pos.right - baseSizeHalf.x,-pos.bottom + baseSizeHalf.y,0.0f),color,uvs[12]},  //12
			{Vec3(+pos.right                 ,-pos.bottom + baseSizeHalf.y,0.0f),color,uvs[13]},  //13
			{Vec3(+pos.right - baseSizeHalf.x,-pos.bottom                 ,0.0f),color,uvs[14]},  //14
			{Vec3(+pos.right                 ,-pos.bottom                 ,0.0f),color,uvs[15]},  //15

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
		drawComp->SetTextureResource(L"Frame");
		drawComp->SetSamplerState(SamplerState::AnisotropicWrap); //テクスチャの繰り返し設定(Wrap)
		drawComp->SetDepthStencilState(DepthStencilState::Read);

		SetAlphaActive(true); //透明をサポートする&両面描画になる
		SetDrawLayer(1);
	}

	void FrameSprite::UpdateVertices() {
		auto texSize = Utility::GetTextureSize(L"Frame");
		auto size = GetComponent<Transform>()->GetScale();
		Rect2D<float> pos;
		pos.left = (m_size.x * (1 / size.x)) / 2.0f;
		pos.right = (m_size.x * (1 / size.x)) / 2.0f;
		pos.top = (m_size.y * (1 / size.y)) / 2.0f;
		pos.bottom = (m_size.y * (1 / size.y)) / 2.0f;
		auto baseSizeHalf = texSize / 2.0f;
		vector<Vec3> vertexPos = {
			{Vec3(-pos.left                  ,+pos.top                 ,0.0f)},  //0
			{Vec3(-pos.left + baseSizeHalf.x ,+pos.top                 ,0.0f)},  //1
			{Vec3(-pos.left                  ,+pos.top - baseSizeHalf.y,0.0f)},  //2
			{Vec3(-pos.left + baseSizeHalf.x ,+pos.top - baseSizeHalf.y,0.0f)},  //3

			{Vec3(+pos.right - baseSizeHalf.x,+pos.top                 ,0.0f)},  //4
			{Vec3(+pos.right                 ,+pos.top                 ,0.0f)},  //5
			{Vec3(+pos.right - baseSizeHalf.x,+pos.top - baseSizeHalf.y,0.0f)},  //6
			{Vec3(+pos.right                 ,+pos.top - baseSizeHalf.y,0.0f)},  //7

			{Vec3(-pos.left                  ,-pos.bottom + baseSizeHalf.y,0.0f)},  //8
			{Vec3(-pos.left + baseSizeHalf.x ,-pos.bottom + baseSizeHalf.y,0.0f)},  //9
			{Vec3(-pos.left                  ,-pos.bottom                 ,0.0f)},  //10
			{Vec3(-pos.left + baseSizeHalf.x ,-pos.bottom                 ,0.0f)},  //11

			{Vec3(+pos.right - baseSizeHalf.x,-pos.bottom + baseSizeHalf.y,0.0f)},  //12
			{Vec3(+pos.right                 ,-pos.bottom + baseSizeHalf.y,0.0f)},  //13
			{Vec3(+pos.right - baseSizeHalf.x,-pos.bottom                 ,0.0f)},  //14
			{Vec3(+pos.right                 ,-pos.bottom                 ,0.0f)},  //15
		};
		if (vertices.size() != vertexPos.size()) {
			throw BaseException(
				L"サイズが一致しません。",
				L"vertices : " + to_wstring(vertices.size()) + L"vertexPos : " + to_wstring(vertexPos.size()),
				L"FrameSprite:UpdateVertices()"
			);
		}
		for (int i = 0; i < vertexPos.size(); i++) {
			vertices[i].position = vertexPos[i];
		}
		GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
	}

	void FrameSprite::SetSize(Vec2 size) {
		GetComponent<Transform>()->SetScale((Vec3)size);
		UpdateVertices();
	}

	void FrameSprite::SetSize(float size) {
		GetComponent<Transform>()->SetScale(Vec3(size));
		UpdateVertices();
	}

	void FrameSprite::SetPosition(Vec2 pos) {
		GetComponent<Transform>()->SetPosition((Vec3)pos);
	}

	void FrameSprite::SetColor(Col4 color) {
		GetComponent<PCTSpriteDraw>()->SetDiffuse(color);
	}
}
//end basecross
