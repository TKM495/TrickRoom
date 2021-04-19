#include "stdafx.h"
#include "Project.h"

namespace basecross {
	TrickArtBase::TrickArtBase()
		:m_MAX(2), m_tirckFlg(false), m_bProjActive(true)
	{
		SetDir(state::Right);
	}

	void TrickArtBase::SetDir(state dir) {
		m_dir = dir;
		switch (m_dir)
		{
		case state::Right:
			m_dirValue = Vec3(10.0f, 10.0f, -10.0f);
			break;
		case state::Left:
			m_dirValue = Vec3(-10.0f, 10.0f, -10.0f);
			break;
		default:
			// エラー
			break;
		}
	}

	Vec3 TrickArtBase::GetDirValue(state dir) {
		switch (dir)
		{
		case state::Right:
			return Vec3(10.0f, 10.0f, -10.0f);
			break;
		case state::Left:
			return Vec3(-10.0f, 10.0f, -10.0f);
			break;
		default:
			// エラー
			break;
		}
		return Vec3(0.0f);
	}
}
// end basecross