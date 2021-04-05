/*!
@file BaseMenu.h
@brief メニューの制御クラス
*/

#pragma once
#include "stdafx.h"
#include "StringSprite2.h"
#include "Cursor.h"

namespace basecross {
    // メニュー項目の表示に必要な構造体を用意する
    struct MenuElement {
        Vec2 pos;        // 座標格納用変数
        wstring name;    // 項目名格納用変数
        wstring sendMsg; // 送るメッセージ
    };

    class BaseMenu :public GameObject {
    protected:
        enum class MenuDirection {
            Vertical,   //垂直方向
            Horizontal  //水平方向
        };

        //メニュー要素のベクター配列
        vector<MenuElement> m_menuElement;
        //メニューの文字
        vector<shared_ptr<StringSprite2>> m_spriteMenu;
        //メニューの要素数
        int m_menuNum;
        //今選択しているメニュー
        int m_nowMenuNum;
        //カーソルオブジェクト
        weak_ptr<Cursor> m_cursor;
        //カーソルの移動方向
        MenuDirection m_dir;
        //遷移遅延
        float m_delayTime;
        //遷移フラグ
        bool m_bChange;
        //時間計測用
        float m_delta;

        //メニュー構築
        void SetUpMenu();
        //ボタンが押されたときの処理
        virtual void OnPushButton();
        //シーンが遷移するときの処理
        virtual void SendEvent(wstring mes);
        //ボタンが押されてから遷移までの時間
        void SetDelayTime(float time) {
            m_delayTime = time;
        }

    public:
        BaseMenu(const shared_ptr<Stage>& stage)
            :GameObject(stage),
            m_menuNum(0),
            m_nowMenuNum(0),
            m_dir(MenuDirection::Vertical),
            m_delayTime(0.0f),
            m_bChange(false),
            m_delta(0.0f)
        {}

        virtual void OnCreate()override {}
        virtual void OnUpdate()override;
    };
}
//end basecross
