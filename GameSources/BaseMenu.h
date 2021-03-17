/*!
@file BaseMenu.h
@brief ���j���[�̐���N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
    // ���j���[���ڂ̕\���ɕK�v�ȍ\���̂�p�ӂ���
    struct MenuElement {
        Vec2 pos;       // ���W�i�[�p�ϐ�
        wstring name; // ���ږ��i�[�p�ϐ�
    };

    class BaseMenu :public GameObject {
    protected:
        //���j���[�v�f�̃x�N�^�[�z��
        vector<MenuElement> m_menuElement;
        //���j���[�̗v�f��
        int m_menuNum;
        //���I�����Ă��郁�j���[
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
