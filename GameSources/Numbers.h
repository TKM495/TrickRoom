#pragma once
#include "stdafx.h"
#include "StringSprite2.h"

namespace basecross {
	class Numbers : public GameObject
	{
		int number;
		Vec2 m_origin;
		Vec2 m_size;
		std::vector<VertexPositionColorTexture> vertices;

	public:
		Numbers(const std::shared_ptr<Stage>& stage, int number)
			:GameObject(stage), number(number)
		{
		}

		void OnCreate() override;
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

		int Numbers::SearchDataIndex(vector<SpriteDataFormat>& data);
	};
}