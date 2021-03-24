#include "stdafx.h"
#include "MyMath.h"

namespace basecross {
	Vec3 MyMath::Leap(Vec3& A, Vec3& B, float f)
	{
		if (f < 0)
		{
			f = 0;
		}

		if (f > 1)
		{
			f = 1;
		}

		Vec3 C = B - A;
		C *= f;
		return A + C;
	}

}