/*!
@file BaseMenu.h
@brief ���j���[�̐���N���X
*/

#pragma once
#include "stdafx.h"
#include "StringSprite2.h"
#include "Cursor.h"

namespace basecross {
    // ���j���[���ڂ̕\���ɕK�v�ȍ\���̂�p�ӂ���
    struct MenuElement {
        Vec2 pos;       // ���W�i�[�p�ϐ�
        wstring name; // ���ږ��i�[�p�ϐ�
        wstring sendMsg; //���郁�b�Z�[�W
    };

    class BaseMenu :public GameObject {
    protected:
        enum class MenuDirection {
            Vertical,   //��������
            Horizontal  //��������
        };

        //���j���[�v�f�̃x�N�^�[�z��
        vector<MenuElement> m_menuElement;
        //���j���[�̕���
        vector<shared_ptr<StringSprite2>> m_spriteMenu;
        //���j���[�̗v�f��
        int m_menuNum;
        //���I�����Ă��郁�j���[
        int m_nowMenuNum;
        //�J�[�\���I�u�W�F�N�g
        weak_ptr<Cursor> m_cursor;
        //����
        MenuDirection m_dir;
    public:
        BaseMenu(const shared_ptr<Stage>& stage)
            :GameObject(stage),
            m_menuNum(0),
            m_nowMenuNum(0),
            m_dir(MenuDirection::Vertical)
        {}

        virtual void OnCreate()override {}
        virtual void OnUpdate()override;
        void SetUpMenu();
    };
}
//end basecross
