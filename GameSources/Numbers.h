#pragma once
#include "stdafx.h"
#include "StringSprite2.h"

namespace basecross {
	class Numbers : public GameObject
	{
		//時間計測用
		float m_delta;
		//非アクティブになるまでの時間
		float m_deActiveTime;
		//非アクティブかどうか
		bool m_bDeactive;
		int number;
		Vec2 m_origin;
		Vec2 m_size;
		Col4 m_color;
		std::vector<VertexPositionColorTexture> vertices;

	public:
		Numbers(const std::shared_ptr<Stage>& stage, int number,
			Col4 color = Col4(0.0f, 0.0f, 0.0f, 1.0f))
			:GameObject(stage), number(number),
			m_color(color),
			m_delta(0.0f),m_bDeactive(false)
		{
		}

		void OnCreate() override;
		void OnUpdate() override;

		void SetValue(int value)
		{
			number = value;
			float fNumber = static_cast<float>(number);
			auto origin = m_origin;
			origin.x += number * m_size.x;
			vertices[0].textureCoordinate = Vec2((origin) / 1024.0f);
			vertices[1].textureCoordinate = Vec2((origin + Vec2(m_size.x, 0.0f)) / 1024.0f);
			vertices[2].textureCoordinate = Vec2((origin + Vec2(0.0f, m_size.y)) / 1024.0f);
			vertices[3].textureCoordinate = Vec2((origin + m_size) / 1024.0f);
			auto drawComp = GetComponent<PCTSpriteDraw>();
			drawComp->UpdateVertices(vertices);
		}

		shared_ptr<FadeComponent> GetFadeComp() {
			return GetComponent<FadeComponent>();
		}

		void Deactive(float time) {
			m_deActiveTime = time;
			SetUpdateActive(true);
		}
		void Deactive() {
			Deactive(0.0f);
		}

		void SetSize(float size) {
			GetComponent<Transform>()->SetScale(Vec3(size));
		}

		int Numbers::SearchDataIndex(vector<SpriteDataFormat>& data);
	};
}