/*!
@file InputHandler.h
@brief ���̓n���h���[
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	template<typename T>
	struct InputHandler {
		void PushHandle(const shared_ptr<T>& Obj) {
			//�L�[�{�[�h�̎擾�i�D��j
			auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
			if (KeyState.m_bPressedKeyTbl[VK_SPACE]) {
				Obj->OnPushA();
				return;
			}
			if (KeyState.m_bPressedKeyTbl['B']) {
				Obj->OnPushB();
				return;
			}
			//�R���g���[���̎擾
			auto pad = App::GetApp()->GetInputDevice().GetControlerVec()[0];
			if (pad.bConnected) {
				//A�{�^��
				if (pad.wPressedButtons & XINPUT_GAMEPAD_A) {
					Obj->OnPushA();
				}
				//B�{�^��
				if (pad.wPressedButtons & XINPUT_GAMEPAD_B) {
					Obj->OnPushB();
				}
				////X�{�^��
				//if (pad.wPressedButtons & XINPUT_GAMEPAD_X) {
				//	Obj->OnPushX();
				//}
				////Y�{�^��
				//if (pad.wPressedButtons & XINPUT_GAMEPAD_Y) {
				//	Obj->OnPushY();
				//}
				//�X�^�[�g�{�^��
				if (pad.wPressedButtons & XINPUT_GAMEPAD_START) {
					Obj->OnPushStart();
				}
				////�o�b�N�{�^��
				//if (pad.wPressedButtons & XINPUT_GAMEPAD_BACK) {
				//	Obj->OnPushBack();
				//}
			}
		}
		Vec3 StickHandle() {
			//�R���g���[���̎擾
			auto pad = App::GetApp()->GetInputDevice().GetControlerVec()[0];
			if (pad.bConnected) {
				return Vec3(pad.fThumbLX, 0.0f, pad.fThumbLY);
			}
			else {
				return Vec3(0.0f);
			}
		}
	};


}

//end basecross

