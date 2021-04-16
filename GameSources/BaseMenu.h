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
        Vec2 pos;           // ���W�i�[�p�ϐ�
        wstring name;       // ���ږ��i�[�p�ϐ�
        wstring sendMsg;    // ���郁�b�Z�[�W
        bool flg = true;           // �L������
    };

    class BaseMenu :public GameObject {
    protected:
        enum class MenuDirection {
            Vertical,   //��������
            Horizontal  //��������
        };
    private:
        //���j���[�v�f�̃x�N�^�[�z��
        vector<MenuElement> m_menuElement;
        //���j���[�̕���
        vector<shared_ptr<StringSprite2>> m_spriteMenu;
        //�I�[�f�B�I�擾�p
        shared_ptr<XAudio2Manager> m_audio;
        //���j���[�̗v�f��
        int m_menuNum;
        //���I�����Ă��郁�j���[
        int m_nowMenuNum;
        //�J�[�\���I�u�W�F�N�g
        weak_ptr<Cursor> m_cursor;
        //�J�[�\���̈ړ�����
        MenuDirection m_dir;
        //�J�ڒx��
        float m_delayTime;
        //�J�ڃt���O
        bool m_bChange;
        //���Ԍv���p
        float m_delta;
        //�J�[�\���̈ړ����x
        float m_cursorSp;
    protected:
        //���j���[�\�z
        template<typename T_Object, typename T_Cursor>
        void SetUpMenu() {
            //-1�Ȃ͔̂z��ɍ��킹�邽��
            m_menuNum = (int)m_menuElement.size() - 1;

            auto& stage = GetStage();
            for (auto& element : m_menuElement) {
                auto str = stage->AddGameObject<T_Object>(element.name);
                str->GetComponent<Transform>()->SetPosition((Vec3)element.pos);
                m_spriteMenu.push_back(str);
            }

            m_cursor = GetStage()->AddGameObject<T_Cursor>();
        }
        //�{�^���������ꂽ�Ƃ��̏���
        virtual void OnPushButton(MenuElement element);
        virtual void OnPushButton(wstring mes);
        virtual void OnPushButton();
        //�V�[�����J�ڂ���Ƃ��̏���
        virtual void SendEvent(wstring mes);
        //���Z�b�g�O�̏���
        virtual void BeforeReset() {}
        //���Z�b�g
        virtual void Reset();
        //�{�^����������Ă���J�ڂ܂ł̎��Ԃ̐ݒ�
        void SetDelayTime(float time) {
            m_delayTime = time;
        }
        //���j���[�v�f��z��ɓ����
        void PushBackElement(const MenuElement& element) {
            m_menuElement.push_back(element);
        }
        //���j���[�̈ړ������̐ݒ�
        void SetMenuDirection(MenuDirection dir) {
            m_dir = dir;
        }
        //�J�ڃt���O�������Ă��邩
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
            m_delta(0.0f),
            m_cursorSp(10.0f),
            m_audio(App::GetApp()->GetXAudio2Manager())
        {}

        virtual void OnCreate()override {}
        virtual void OnUpdate()override;

        //���j���[�̕\���A��\��
        void SetDrawMenu(bool flg);
    };
}
//end basecross
