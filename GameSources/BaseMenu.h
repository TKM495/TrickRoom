/*!
@file BaseMenu.h
@brief メニューの制御クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    // メニュー項目の表示に必要な構造体を用意する
    struct MenuElement {
        Vec2 pos;       // 座標格納用変数
        wstring name; // 項目名格納用変数
    };

    class BaseMenu :public GameObject {
    protected:
        //メニュー要素のベクター配列
        vector<MenuElement> m_menuElement;
        //メニューの要素数
        int m_menuNum;
        //今選択しているメニュー
        int m_nowMenuNum;
    public:
        BaseMenu(const shared_ptr<Stage>& stage)
            :GameObject(stage),
            m_menuNum(0),
            m_nowMenuNum(0)
        {}

        virtual void OnCreate()override {}
        virtual void OnUpdate()override {}
    };
}
//end basecross
