#include "stdafx.h"
#include "Project.h"

namespace basecross {
	TrickArtBase::TrickArtBase()
	{
		SetDir(TADirection::Right);
	}

	void TrickArtBase::SetDir(TADirection dir) {
		m_dir = dir;
		switch (m_dir)
		{
		case TADirection::Right:
			m_dirValue = Vec3(10.0f, 10.0f, -10.0f);
			break;
		case TADirection::Left:
			m_dirValue = Vec3(-10.0f, 10.0f, -10.0f);
			break;
		case TADirection::MAX:
			throw BaseException(
				L"���̒l�͎g�p�ł��܂���B",
				L"name : TADirection::MAX",
				L"TrickArtBase::SetDir()"
			);
			break;
		default:
			// �G���[
			break;
		}
	}

	Vec3 TrickArtBase::GetDirValue(TADirection dir) {
		switch (dir)
		{
		case TADirection::Right:
			return Vec3(10.0f, 10.0f, -10.0f);
			break;
		case TADirection::Left:
			return Vec3(-10.0f, 10.0f, -10.0f);
			break;
		case TADirection::MAX:
			throw BaseException(
				L"���̒l�͎g�p�ł��܂���B",
				L"name : TADirection::MAX",
				L"TrickArtBase::SetDir()"
			);
			break;
		default:
			// �G���[
			break;
		}
		return Vec3(0.0f);
	}
}
// end basecross