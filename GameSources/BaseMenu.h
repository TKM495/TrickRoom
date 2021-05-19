/*!
@file BaseMenu.h
@brief メニューの制御クラス
*/

#pragma once
#include "stdafx.h"
#include "StringSprite2.h"
#include "illusionFrame.h"
#include "Cursor.h"

namespace basecross {
    // メニュー項目の表示に必要な構造体を用意する
    struct MenuElement {
        Vec2 pos;           // 座標格納用変数
        wstring name;       // 項目名格納用変数
        wstring sendMsg;    // 送るメッセージ
        bool flg = true;           // 有効無効
    };

    class BaseMenu :public GameObject {
    protected:
        enum class MenuDirection {
            Vertical,   //垂直方向
            Horizontal  //水平方向
        };
    private:
        //メニュー要素のベクター配列
        vector<MenuElement> m_menuElement;
        //メニューの文字
        vector<shared_ptr<StringSprite2>> m_stringSprite;
        //メニューの文字のフレーム
        vector<shared_ptr<illusionFrame>> m_illusionFrame;
        //オーディオ取得用
        shared_ptr<XAudio2Manager> m_audio;
        //メニューの要素数
        int m_menuNum;
        //今選択しているメニュー
        int m_nowMenuNum;
        //カーソルの移動方向
        MenuDirection m_dir;
        //遷移遅延
        float m_delayTime;
        //遷移フラグ
        bool m_bChange;
        //遅延時間計測用
        float m_delayDelta;
        //点滅の時間計測用
        float m_delta;
        //点滅のレート
        float m_rate;
        //カーソルの移動速度
        float m_cursorSp;
        //メニューの現在の状態
        bool m_bActive;
    protected:
        //メニュー構築
        void SetUpMenu();
        //ボタンが押されたときの処理
        virtual void OnPushButton(MenuElement element);
        virtual void OnPushButton(wstring mes);
        virtual void OnPushButton();
        //シーンが遷移するときの処理
        virtual void SendEvent(wstring mes);
        //リセット前の処理
        virtual void BeforeReset() {}
        virtual void PlayDecisionSE();
        virtual void PlayDecisionSE(wstring mes);
        //ボタンが押されてから遷移までの時間の設定
        void SetDelayTime(float time) {
            m_delayTime = time;
        }
        //メニュー要素を配列に入れる
        void PushBackElement(const MenuElement& element) {
            m_menuElement.push_back(element);
        }
        //メニューの移動方向の設定
        void SetMenuDirection(MenuDirection dir) {
            m_dir = dir;
        }
        //遷移フラグが立っているか
        bool IsChange() {
            return m_bChange;
        }
        vector<MenuElement>& GetMenuElement() {
            return m_menuElement;
        }

    public:
        BaseMenu(const shared_ptr<Stage>& stage)
            :GameObject(stage),
            m_menuNum(0),
            m_nowMenuNum(0),
            m_dir(MenuDirection::Vertical),
            m_delayTime(0.0f),
            m_bChange(false),
            m_delayDelta(0.0f),
            m_delta(0.0f),
            m_cursorSp(10.0f),
            m_audio(App::GetApp()->GetXAudio2Manager()),
            m_bActive(true),
            m_rate(4.0f)
        {}

        virtual void OnCreate()override {}
        virtual void OnUpdate()override;

        //メニューの表示、非表示
        void SetDrawMenu(bool flg);
        //リセット
        virtual void Reset();

    };
}
//end basecross
