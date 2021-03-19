#pragma once
#include "stdafx.h"

namespace basecross {
	class Numbers : public GameObject
	{
		int number;
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
			vertices[0].textureCoordinate = Vec2((fNumber + 0) * 50.0f / 512.0f, 100.0f / 512.0f);
			vertices[1].textureCoordinate = Vec2((fNumber + 1) * 50.0f / 512.0f, 100.0f / 512.0f);
			vertices[2].textureCoordinate = Vec2((fNumber + 0) * 50.0f / 512.0f, 200.0f / 512.0f);
			vertices[3].textureCoordinate = Vec2((fNumber + 1) * 50.0f / 512.0f, 200.0f / 512.0f);
			auto drawComp = GetComponent<PCTSpriteDraw>();
			drawComp->UpdateVertices(vertices);
		}
	};
}