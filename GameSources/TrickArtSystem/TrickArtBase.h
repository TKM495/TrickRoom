#pragma once
#include "stdafx.h"
#include "MainCamera.h"
#include "AdvCollision.h"

namespace basecross {
	class TrickArtBase{
		Vec3 m_dirValue;
		int m_MAX;
		state m_dir;
	protected:
		//�g���b�N�A�[�g���e�t���O
		bool m_bProjActive;
		//�g���b�N�A�[�g�Ƃ��ĕ`�悷�邩
		bool m_trickFlg;
		//�g���b�N�A�[�g�̂Ƃ��ǂ̕������猩�邩
		state m_activeState;
		//�����蔻��̂��
		vector<shared_ptr<AdvCollision>> m_myCols;

		//���̃N���X���p�������I�u�W�F�N�g�̕����x�N�g�����擾
		Vec3 GetMyDirValue() {
			return m_dirValue;
		}
	public:
		TrickArtBase();

		//TADirection�̍��ڂ̐���Ԃ�(1�`)
		int GetTypeNum() {
			return m_MAX;
		}
		//���g�̕������Z�b�g
		//(�R���|�[�l���g�����̊֐����g������public)
		void SetDir(state dir);
		//���g�̕������擾
		state GetDir() {
			return m_dir;
		}
		//����̕����̕����x�N�g�����擾
		static Vec3 GetDirValue(state dir);

		void UpdateArt(const shared_ptr<Camera>& cam);

		template<typename T>
		void UpdateArt(const shared_ptr<Camera>& cam,const shared_ptr<T>& col) {
			if (!m_trickFlg) {
				return;
			}
			auto camera = dynamic_pointer_cast<MainCamera>(cam);
			state nowState = camera->GetCamState();
			if (nowState == m_activeState) {
				col->SetUpdateActive(true);
			}
			else {
				col->SetUpdateActive(false);
			}
		}
	};
}
// end basecross