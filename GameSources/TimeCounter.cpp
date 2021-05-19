/*!
@file TimeCounter.cpp
@brief ���Ԍv���N���X����
*/

#include "stdafx.h"
#include "TimeCounter.h"

namespace basecross {
	bool TimeCounter::Count() {
		return Count(0.0f);
	}
	bool TimeCounter::Count(float offset) {
		auto elapsed = App::GetApp()->GetElapsedTime();
		bool flg = false;
		if (m_countTime - offset < m_delta) {
			flg = true;
		}
		else {
			flg = false;
		}

		//�O�̂��ߎw�肵�����Ԃ��o�߂������~������
		if (m_countTime >= m_delta) {
			m_delta += elapsed;
		}
		return flg;
	}
}
//end basecross