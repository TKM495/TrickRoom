/*!
@file SelectStageMenu.h
@brief ステージセレクトのメニュークラス
*/

#pragma once
#include "stdafx.h"
#include "PictureFrame.h"
#include "BGSprite.h"

namespace basecross {
	class SelectStageMenu :public GameObject {
        //額
        vector<shared_ptr<PictureFrame>> m_picFrame;
        vector<shared_ptr<BGSprite>> m_bgObj;
        //オーディオ取得用
        shared_ptr<XAudio2Manager> m_audio;
        //カーソルオブジェクト
        weak_ptr<Cursor> m_cursor;
        vector<Vec2> m_menuGroupPos;
        vector<Vec2> m_menuItemPos;
        vector<Vec2> m_menuItemBasePos;
        //メニューの要素数
        int m_menuNum;
        //今選択しているメニュー
        int m_nowMenuNum;
        //メニューグループ
        int m_nowMenuGroupNum;
        Vec2 m_nowmenuGroupPos;
        int m_beforeMenuGroupNum;
        Vec2 m_beforeMenuGroupPos;
        wstring m_mes;
        //遷移遅延
        float m_delayTime;
        //遷移フラグ
        bool m_bChange;
        //時間計測用
        float m_delta;
        //カーソルの移動速度
        float m_cursorSp;
        //ボタンが押されたときの処理
        virtual void OnPushButton(wstring mes);
        virtual void OnPushButton();
        //シーンが遷移するときの処理
        virtual void SendEvent(wstring mes);
        //リセット
        virtual void Reset();
        //ボタンが押されてから遷移までの時間の設定
        void SetDelayTime(float time) {
            m_delayTime = time;
        }
        //遷移フラグが立っているか
        bool IsChange() {
            return m_bChange;
        }

    public:
        SelectStageMenu(const shared_ptr<Stage>& stage)
            :GameObject(stage),
            m_menuNum(0),
            m_nowMenuNum(0),
            m_nowMenuGroupNum(0),
            m_delayTime(0.0f),
            m_bChange(false),
            m_delta(0.0f),
            m_cursorSp(10.0f),
            m_mes(L""),
            m_audio(App::GetApp()->GetXAudio2Manager())
        {}

        virtual void OnCreate()override;
        virtual void OnUpdate()override;

        //メニューの表示、非表示
        void SetDrawMenu(bool flg);
    };
}
//end basecross
