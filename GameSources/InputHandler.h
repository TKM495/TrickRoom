/*!
@file InputHandler.h
@brief 入力ハンドラー
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	template<typename T>
	struct InputHandler {
		void PushHandle(const shared_ptr<T>& Obj) {
			//キーボードの取得（優先）
			auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
			if (KeyState.m_bPressedKeyTbl[VK_SPACE]) {
				Obj->OnPushA();
				return;
			}
			if (KeyState.m_bPressedKeyTbl['B']) {
				Obj->OnPushB();
				return;
			}
			//コントローラの取得
			auto pad = App::GetApp()->GetInputDevice().GetControlerVec()[0];
			if (pad.bConnected) {
				//Aボタン
				if (pad.wPressedButtons & XINPUT_GAMEPAD_A) {
					Obj->OnPushA();
				}
				//Bボタン
				if (pad.wPressedButtons & XINPUT_GAMEPAD_B) {
					Obj->OnPushB();
				}
				////Xボタン
				//if (pad.wPressedButtons & XINPUT_GAMEPAD_X) {
				//	Obj->OnPushX();
				//}
				////Yボタン
				//if (pad.wPressedButtons & XINPUT_GAMEPAD_Y) {
				//	Obj->OnPushY();
				//}
				//スタートボタン
				if (pad.wPressedButtons & XINPUT_GAMEPAD_START) {
					Obj->OnPushStart();
				}
				////バックボタン
				//if (pad.wPressedButtons & XINPUT_GAMEPAD_BACK) {
				//	Obj->OnPushBack();
				//}
			}
		}
		Vec3 StickHandle() {
			//コントローラの取得
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

