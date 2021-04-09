/*!
@file ColorOut.cpp
@brief �u���b�N�A�E�g�Ȃǂ̃N���X����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void ColorOut::OnCreate() {
		GetStage()->SetSharedGameObject(L"ColorOut", GetThis<ColorOut>());

		auto viewport = GetStage()->GetView()->GetTargetViewport();

		auto halfWidth = viewport.Width / 2.0f;
		auto halfHeight = viewport.Height / 2.0f;

		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		std::vector<VertexPositionColor> vertices = {
			{Vec3(-halfWidth, +halfHeight, 0.0f), color},
			{Vec3(+halfWidth, +halfHeight, 0.0f), color},
			{Vec3(-halfWidth, -halfHeight, 0.0f), color},
			{Vec3(+halfWidth, -halfHeight, 0.0f), color}
		};
		std::vector<uint16_t> indices = {
			0, 1, 2,
			2, 1, 3
		};
		auto drawComp = AddComponent<PCSpriteDraw>(vertices, indices);
		drawComp->SetTextureResource(L"ColorOut");
		drawComp->SetDiffuse(m_color);

		SetAlphaActive(true);
		//SetDrawLayer(0);
		SetActive(false);
	}

	void ColorOut::OnUpdate() {
		auto delta = App::GetApp()->GetElapsedTime();

		auto time = sinf(m_delta);

		auto alpha = Lerp::CalculateLerp(m_min, m_max, -1.0f, 1.0f, time, Lerp::rate::Linear);

		auto drawComp = GetComponent<PCSpriteDraw>();
		Col4 color = m_color;
		color.w = alpha;
		drawComp->SetDiffuse(color);

		m_delta += delta * m_rate;
		if (m_delta >= XM_2PI) {
			m_delta = 0.0f;
		}
	}

	void ColorOut::SetRange(float max, float min) {
		if (RangeCheck(max, min)) {
			m_max = max;
			m_min = min;
		}
	}

	bool ColorOut::RangeCheck(float max, float min) {
		if (max > min) {
			return true;
		}
		else {
			throw BaseException(
				L"�l���������傫�����t�ɂȂ��Ă��܂�",
				L"max : " + to_wstring(max) + L", min : " + to_wstring(min),
				L"ColorOut::SetRange(float max, float min)"
			);
		}
	}
}
//end basecross
