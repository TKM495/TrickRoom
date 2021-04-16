/*!
@file SelectStageMenu.h
@brief �X�e�[�W�Z���N�g�̃��j���[�N���X
*/

#pragma once
#include "stdafx.h"
#include "PictureFrame.h"
#include "BGSprite.h"

namespace basecross {
	class SelectStageMenu :public GameObject {
        //�z
        vector<shared_ptr<PictureFrame>> m_picFrame;
        vector<shared_ptr<BGSprite>> m_bgObj;
        vector<Vec3> m_picFramePos;
        //�I�[�f�B�I�擾�p
        shared_ptr<XAudio2Manager> m_audio;

        //���j���[�̗v�f��
        int m_menuNum;
        //���I�����Ă��郁�j���[
        int m_nowMenuNum;
        //�ȑO�I�����Ă������j���[
        int m_beforeMenuNum;
        wstring m_mes;
        Vec3 m_nowPos;
        //�J�ڒx��
        float m_delayTime;
        //�J�ڃt���O
        bool m_bChange;
        //���Ԍv���p
        float m_delta;
        //�J�[�\���̈ړ����x
        float m_cursorSp;
        //�{�^���������ꂽ�Ƃ��̏���
        virtual void OnPushButton(wstring mes);
        virtual void OnPushButton();
        //�V�[�����J�ڂ���Ƃ��̏���
        virtual void SendEvent(wstring mes);
        //���Z�b�g
        virtual void Reset();
        //�{�^����������Ă���J�ڂ܂ł̎��Ԃ̐ݒ�
        void SetDelayTime(float time) {
            m_delayTime = time;
        }
        //�J�ڃt���O�������Ă��邩
        bool IsChange() {
            return m_bChange;
        }

    public:
        SelectStageMenu(const shared_ptr<Stage>& stage)
            :GameObject(stage),
            m_menuNum(0),
            m_nowMenuNum(0),
            m_delayTime(0.0f),
            m_bChange(false),
            m_delta(0.0f),
            m_cursorSp(5.0f),
            m_nowPos(Vec3(0.0f)),
            m_mes(L""),
            m_audio(App::GetApp()->GetXAudio2Manager())
        {}

        virtual void OnCreate()override;
        virtual void OnUpdate()override;

        //���j���[�̕\���A��\��
        void SetDrawMenu(bool flg);
    };
}
//end basecross
