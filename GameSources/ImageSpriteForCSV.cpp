/*!
@file ImageSpriteForCSV.cpp
@brief �摜�\���p�N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void ImageSpriteForCSV::OnCreate() {
		//CSVLoad���擾���f�[�^�����炤
		auto csvLoad = dynamic_pointer_cast<CSVLoad>(GetStage()->GetSharedObject(L"CSVLoad"));
		auto& data = csvLoad->GetImageSpriteData();
		//�ڕW�̃f�[�^��T��
		int index = Utility::SearchDataIndex(data, m_name);
		if (index == -1) {
			throw BaseException(
				L"�ڕW�̃f�[�^��������܂���",
				L"name : " + m_name,
				L"ImageSpriteForCSV::OnCreate()"
			);
		}
		m_data = data[index];
		auto origin = m_data.origin;
		auto size = m_data.size;
		Rect2D<float> pos;
		//�c�ʒu�̐ݒ�
		switch (m_horizontal)
		{
		case basecross::Align::Horizontal::Left:
			pos.left = 0.0f;
			pos.right = size.x;
			break;
		case basecross::Align::Horizontal::Center:
			pos.left = size.x / 2.0f;
			pos.right = size.x / 2.0f;
			break;
		case basecross::Align::Horizontal::Right:
			pos.left = size.x;
			pos.right = 0.0f;
			break;
		default:
			//�G���[
			break;
		}
		//���ʒu�̐ݒ�
		switch (m_vertical)
		{
		case basecross::Align::Vertical::Top:
			pos.top = 0.0f;
			pos.bottom = size.y;
			break;
		case basecross::Align::Vertical::Center:
			pos.top = size.y / 2.0f;
			pos.bottom = size.y / 2.0f;
			break;
		case basecross::Align::Vertical::Bottom:
			pos.top = size.y;
			pos.bottom = 0.0f;
			break;
		default:
			//�G���[
			break;
		}
		vector<Vec2> uvs,uv = {
			origin,
			origin + Vec2(size.x,0.0f),
			origin + Vec2(0.0f, size.y),
			origin + size
		};
		Utility::ConvertToUVCoordinates(uv, L"Sprite", uvs);
		//���_�̃f�[�^
		vertices = {
			{Vec3(-pos.left,+pos.top,0.0f),m_color,uvs[0]}, //0
			{Vec3(+pos.right,+pos.top,0.0f),m_color,uvs[1]}, //1

			{Vec3(-pos.left,-pos.bottom,0.0f),m_color,uvs[2]}, //2
			{Vec3(+pos.right,-pos.bottom,0.0f),m_color,uvs[3]},  //3
		};
		//���_�C���f�b�N�X
		vector<uint16_t> indices = {
			0, 1, 2, //��̎O�p�`
			2, 1, 3 //���̎O�p�`
		};

		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);
		drawComp->SetTextureResource(L"Sprite");
		drawComp->SetSamplerState(SamplerState::AnisotropicWrap); //�e�N�X�`���̌J��Ԃ��ݒ�(Wrap)
		drawComp->SetDepthStencilState(DepthStencilState::Read);

		auto fade = AddComponent<FadeComponent>();
		fade->SetFadeColor(m_color);

		SetAlphaActive(true); //�������T�|�[�g����&���ʕ`��ɂȂ�
		//GetComponent<Transform>()->SetScale(Vec3(0.005f));

		SetUpdateActive(false);
	}

	void ImageSpriteForCSV::OnUpdate() {
		auto delta = App::GetApp()->GetElapsedTime();
		auto fade = GetComponent<FadeComponent>();
		if (m_delta > m_deActiveTime && !m_bDeactive) {
			fade->FadeOut();
			m_bDeactive = true;
		}

		if (!fade->IsFadeActive() && m_bDeactive) {
			m_delta = 0.0f;
			m_bDeactive = false;
			SetDrawActive(false);
			SetUpdateActive(false);
		}
		m_delta += delta;
	}

	int ImageSpriteForCSV::SearchDataIndex(vector<SpriteDataFormat>& data) {
		for (int i = 0; i < data.size(); i++) {
			if (data[i].name == m_name) {
				return i;
			}
		}
		//�����ɗ�����Ȃ�
		return -1;
	}

	void ImageSpriteForCSV::SetAlignHorizontal(Align::Horizontal hor) {
		auto origin = m_data.origin;
		auto size = m_data.size;
		m_horizontal = hor;
		Rect2D<float> pos;
		//�c�ʒu�̐ݒ�
		switch (m_horizontal)
		{
		case basecross::Align::Horizontal::Left:
			pos.left = 0.0f;
			pos.right = size.x;
			break;
		case basecross::Align::Horizontal::Center:
			pos.left = size.x / 2.0f;
			pos.right = size.x / 2.0f;
			break;
		case basecross::Align::Horizontal::Right:
			pos.left = size.x;
			pos.right = 0.0f;
			break;
		default:
			//�G���[
			break;
		}
		vertices[0].position.x = vertices[2].position.x = -pos.left;
		vertices[1].position.x = vertices[3].position.x = +pos.right;
		GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
	}

	void ImageSpriteForCSV::SetAlignVertical(Align::Vertical ver) {
		auto origin = m_data.origin;
		auto size = m_data.size;
		m_vertical = ver;
		Rect2D<float> pos;
		//���ʒu�̐ݒ�
		switch (m_vertical)
		{
		case basecross::Align::Vertical::Top:
			pos.top = 0.0f;
			pos.bottom = size.y;
			break;
		case basecross::Align::Vertical::Center:
			pos.top = size.y / 2.0f;
			pos.bottom = size.y / 2.0f;
			break;
		case basecross::Align::Vertical::Bottom:
			pos.top = size.y;
			pos.bottom = 0.0f;
			break;
		default:
			//�G���[
			break;
		}
		vertices[0].position.y = vertices[1].position.y = +pos.top;
		vertices[2].position.y = vertices[3].position.y = -pos.bottom;
		GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
	}

	void ImageSpriteForCSV::SetSize(float size) {
		GetComponent<Transform>()->SetScale(Vec3(size));
	}

	void ImageSpriteForCSV::SetPos(Vec3 pos) {
		GetComponent<Transform>()->SetPosition(pos);
	}

	void ImageSpriteForCSV::SetRot(float rot) {
		GetComponent<Transform>()->SetRotation(0.0f, 0.0f, XMConvertToRadians(rot));
	}

	float ImageSpriteForCSV::GetRot() {
		//�傫���͓����Ȃ̂łƂ肠����x��Ԃ�
		return GetComponent<Transform>()->GetRotation().z;
	}

	float ImageSpriteForCSV::GetSize() {
		//�傫���͓����Ȃ̂łƂ肠����x��Ԃ�
		return GetComponent<Transform>()->GetScale().x;
	}

	Vec3 ImageSpriteForCSV::GetPos() {
		return GetComponent<Transform>()->GetPosition();
	}
}
//end basecross