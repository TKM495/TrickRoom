#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Numbers::OnCreate()
	{
		//CSVLoadを取得しデータをもらう
		auto csvLoad = dynamic_pointer_cast<CSVLoad>(GetStage()->GetSharedObject(L"CSVLoad"));
		auto& data = csvLoad->GetSpriteData();
		//目標のデータを探す
		int index = SearchDataIndex(data);
		if (index == -1) {
			throw BaseException(
				L"目標のデータが見つかりません",
				L"name : Numbers",
				L"Numbers::OnCreate()"
			);
		}

		auto dat = data[index];

		m_origin = dat.origin;
		m_size = dat.size;
		Rect2D<float> pos;
		pos.left = pos.right = m_size.x / 2.0f;
		pos.top = pos.bottom = m_size.y / 2.0f;

		float fNumber = static_cast<float>(number);
		auto origin = m_origin;
		origin.x += number * m_size.x;
		vertices = {
			{Vec3(-pos.left,+pos.top,0.0f),m_color,(origin) / 1024.0f}, //0
			{Vec3(+pos.right,+pos.top,0.0f),m_color,(origin + Vec2(m_size.x,0.0f)) / 1024.0f}, //1

			{Vec3(-pos.left,-pos.bottom,0.0f),m_color,(origin + Vec2(0.0f,m_size.y)) / 1024.0f}, //2
			{Vec3(+pos.right,-pos.bottom,0.0f),m_color,(origin + m_size) / 1024.0f}  //3
		};
		std::vector<uint16_t> indices = {
			0,1,2,
			2,1,3
		};
		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);
		drawComp->SetTextureResource(L"string");

		SetAlphaActive(true);

		AddComponent<FadeComponent>()->SetFadeColor(m_color);
	}

	int Numbers::SearchDataIndex(vector<SpriteDataFormat>& data) {
		for (int i = 0; i < data.size(); i++) {
			if (data[i].name == L"Numbers") {
				return i;
			}
		}
		//ここに来たらない
		return -1;
	}
}
