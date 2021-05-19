/*!
@file PCTStaticDraw2.cpp
@brief �g���b�N�A�[�g�`��ɑΉ������V�F�[�_�[(���C�e�B���O�Ȃ�)����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	IMPLEMENT_DX11_CONSTANT_BUFFER(CBPCTStaticDraw2)
	IMPLEMENT_DX11_VERTEX_SHADER(VSPCTStaticDraw2, App::GetApp()->GetShadersPath() + L"VSPCTStaticDraw2.cso")
	IMPLEMENT_DX11_PIXEL_SHADER(PSPCTStaticDraw2, App::GetApp()->GetShadersPath() + L"PSPCTStaticDraw2.cso")

	struct PCTStaticDraw2::Impl :public DrawObjectBase {
		//���_�ύX����ꍇ�̃��b�V���i�I���W�i���j
		shared_ptr<MeshResource> m_OriginalMeshResource;
		//�I���W�i�����b�V�����g�����ǂ���
		bool m_UseOriginalMeshResource;
		///�e�N�X�`�����\�[�X
		weak_ptr<TextureResource> m_TextureResource;
		///�G�~�b�V�u�F
		bsm::Col4 m_Emissive;
		/// �f�t���[�Y�F
		bsm::Col4 m_Diffuse;
		/// �X�y�L�����[�F
		bsm::Col4 m_Specular;
		///�e�𓊉e���邩�ǂ���
		bool m_OwnShadowActive;
		//���f���ɓ����Ă���Diffuse���g�����ǂ���
		bool m_ModelDiffusePriority;
		//���f���ɓ����Ă���Emissive���g�����ǂ���
		bool m_ModelEmissivePriority;
		//���f���ɓ����Ă���e�N�X�`�����g�����ǂ���
		bool m_ModelTextureEnabled;
		///Instance�`��p
		///Instance�ő�l
		size_t m_MaxInstance;
		/// �s��p�̒��_�o�b�t�@
		ComPtr<ID3D11Buffer> m_MatrixBuffer;
		///�s��̔z��
		vector<bsm::Mat4x4> m_MatrixVec;
		//�s��������N���A���邩�ǂ���
		bool m_AutoClearMatrixVec;
		PCTStaticDraw2::Impl() :
			m_UseOriginalMeshResource(false),
			m_Emissive(0, 0, 0, 0),
			m_Diffuse(1.0f, 1.0f, 1.0f, 1.0f),
			m_Specular(0, 0, 0, 0),
			m_OwnShadowActive(false),
			m_ModelDiffusePriority(false),
			m_ModelEmissivePriority(false),
			m_ModelTextureEnabled(true),
			m_MaxInstance(2000),
			m_AutoClearMatrixVec(false)
		{}
	};


	PCTStaticDraw2::PCTStaticDraw2(const shared_ptr<GameObject>& GameObjectPtr)
		:SmBaseDraw(GameObjectPtr), pImpl(new Impl())
	{}
	PCTStaticDraw2::~PCTStaticDraw2() {}

	void PCTStaticDraw2::OnCreate() {}

	void PCTStaticDraw2::OnDraw() {
		if (GetGameObject()->GetAlphaActive()) {
			if (!(GetBlendState() == BlendState::AlphaBlend || GetBlendState() == BlendState::Additive)) {
				SetBlendState(BlendState::AlphaBlend);
			}
			SetRasterizerState(RasterizerState::DoubleDraw);
		}
		//���b�V�����\�[�X�̎擾
		auto PtrMeshResource = GetMeshResource();
		if (PtrMeshResource) {
			DrawStatic2(PtrMeshResource->GetMashData());
		}
		//��n��
		auto Dev = App::GetApp()->GetDeviceResources();
		Dev->InitializeStates();

	}

	void PCTStaticDraw2::DrawStatic2(const MeshPrimData& data) {
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
		auto RenderState = Dev->GetRenderState();
		auto scene = App::GetApp()->GetScene<Scene>();
		//NULL�̃V�F�[�_���\�[�X�̏���
		ID3D11ShaderResourceView* pNull[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT] = { nullptr };
		//�T���v���[�̏���
		ID3D11SamplerState* pNullSR[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT] = { nullptr };
		//�e�I�u�W�F�N�g���ʏ���
		//�V�F�[�_�̐ݒ�
		//���_�V�F�[�_
		pD3D11DeviceContext->VSSetShader(VSPCTStaticDraw2::GetPtr()->GetShader(), nullptr, 0);
		//�C���v�b�g���C�A�E�g�̐ݒ�
		pD3D11DeviceContext->IASetInputLayout(VSPCTStaticDraw2::GetPtr()->GetInputLayout());
		//�s�N�Z���V�F�[�_
		pD3D11DeviceContext->PSSetShader(PSPCTStaticDraw2::GetPtr()->GetShader(), nullptr, 0);
		//�ʏ���
		SimpleConstantsEX SmCb;
		//�R���X�^���g�o�b�t�@�̍쐬
		SetConstants2(SmCb, data);
		//�e�N�X�`��
		auto shTex = GetTextureResource();
		if (shTex) {
			//�e�N�X�`��������
			SmCb.ActiveFlg.x = 1;
		}
		else {
			//�`��R���|�[�l���g�ɂ̓e�N�X�`�����Ȃ�
			if (shTex = data.m_TextureResource.lock()) {
				//�e�N�X�`��������
				SmCb.ActiveFlg.x = 1;
			}
			else {
				SmCb.ActiveFlg.x = 0;
			}
		}
		//�R���X�^���g�o�b�t�@�̍X�V
		pD3D11DeviceContext->UpdateSubresource(CBPCTStaticDraw2::GetPtr()->GetBuffer(), 0, nullptr, &SmCb, 0, 0);
		//�R���X�^���g�o�b�t�@�̐ݒ�
		ID3D11Buffer* pConstantBuffer = CBPCTStaticDraw2::GetPtr()->GetBuffer();
		ID3D11Buffer* pNullConstantBuffer = nullptr;
		//���_�V�F�[�_�ɓn��
		pD3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
		//�s�N�Z���V�F�[�_�ɓn��
		pD3D11DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);
		//�X�g���C�h�ƃI�t�Z�b�g
		UINT stride = data.m_NumStride;
		UINT offset = 0;
		//�`����@�̃Z�b�g
		pD3D11DeviceContext->IASetPrimitiveTopology(data.m_PrimitiveTopology);
		//���_�o�b�t�@�̃Z�b�g
		pD3D11DeviceContext->IASetVertexBuffers(0, 1, data.m_VertexBuffer.GetAddressOf(), &stride, &offset);
		//�C���f�b�N�X�o�b�t�@�̃Z�b�g
		pD3D11DeviceContext->IASetIndexBuffer(data.m_IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
		//�e�����_�����O�X�e�[�g�̐ݒ�
		//�u�����h�X�e�[�g
		RenderState->SetBlendState(pD3D11DeviceContext, GetBlendState());
		//�f�v�X�X�e���V���X�e�[�g
		RenderState->SetDepthStencilState(pD3D11DeviceContext, GetDepthStencilState());
		//�e�N�X�`���ƃT���v���[
		if (shTex) {
			pD3D11DeviceContext->PSSetShaderResources(0, 1, shTex->GetShaderResourceView().GetAddressOf());
			//�T���v���[��ݒ�
			RenderState->SetSamplerState(pD3D11DeviceContext, GetSamplerState(), 0);
		}
		else {
			//�V�F�[�_�[���\�[�X���N���A
			pD3D11DeviceContext->PSSetShaderResources(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, pNull);
			//�T���v���[���N���A
			RenderState->SetSamplerAllClear(pD3D11DeviceContext);
		}

		//TrickArtRenderTarget�̎擾
		for (int i = 0; i < 2; i++) {
			shared_ptr<TADrawRenderTarget> TrickArtDraw = dynamic_pointer_cast<GameStage>(GetStage())->GetTADraw(i);
			ID3D11ShaderResourceView* pTrickArtDrawSRV = TrickArtDraw->GetShaderResourceView();
			pD3D11DeviceContext->PSSetShaderResources(1 + i, 1, &pTrickArtDrawSRV);
		}

		//���X�^���C�U�X�e�[�g�ƕ`��
		if (GetRasterizerState() == RasterizerState::DoubleDraw) {
			//���������p
			//���X�^���C�U�X�e�[�g(���`��)
			pD3D11DeviceContext->RSSetState(RenderState->GetCullFront());
			//�`��
			pD3D11DeviceContext->DrawIndexed(data.m_NumIndicis, 0, 0);
			//���X�^���C�U�X�e�[�g�i�\�`��j
			pD3D11DeviceContext->RSSetState(RenderState->GetCullBack());
			//�`��
			pD3D11DeviceContext->DrawIndexed(data.m_NumIndicis, 0, 0);
		}
		else {
			RenderState->SetRasterizerState(pD3D11DeviceContext, GetRasterizerState());
			//�`��
			pD3D11DeviceContext->DrawIndexed(data.m_NumIndicis, 0, 0);
		}
	}

	void PCTStaticDraw2::SetConstants2(SimpleConstantsEX& SmCb, const MeshPrimData& data) {
		//�s��̒�`
		auto PtrTrans = GetGameObject()->GetComponent<Transform>();
		//�s��̒�`
		Mat4x4 World, ViewMat, ProjMat;
		//���[���h�s��̌���
		if (data.m_UseMeshToTransformMatrix) {
			World = data.m_MeshToTransformMatrix * GetMeshToTransformMatrix();
			World *= PtrTrans->GetWorldMatrix();
		}
		else {
			World = GetMeshToTransformMatrix() * PtrTrans->GetWorldMatrix();
		}
		//�]�u����
		World.transpose();
		//�J�����𓾂�
		auto CameraPtr = GetGameObject()->OnGetDrawCamera();
		//�r���[�Ǝˉe�s��𓾂�
		ViewMat = CameraPtr->GetViewMatrix();
		//�]�u����
		ViewMat.transpose();
		//�]�u����
		ProjMat = CameraPtr->GetProjMatrix();
		ProjMat.transpose();
		SmCb.World = World;
		SmCb.View = ViewMat;
		SmCb.Projection = ProjMat;
		//�G�~�b�V�u
		SmCb.Emissive = GetEmissive();
		//�f�t�B�[�Y
		SmCb.Diffuse = GetDiffuse();
		//�X�y�L�����[
		SmCb.Specular = GetSpecular();
		//���C�e�B���O
		auto StageLight = GetGameObject()->OnGetDrawLight();
		SmCb.LightDir = StageLight.m_Directional;
		SmCb.LightDir.w = 1.0f;
		SmCb.EyePos = CameraPtr->GetEye();
		SmCb.EyePos.w = 1.0f;
		bsm::Vec3 CalcLightDir = -1.0 * StageLight.m_Directional;
		bsm::Vec3 LightAt = CameraPtr->GetAt();
		bsm::Vec3 LightEye = CalcLightDir;
		LightEye *= Shadowmap::GetLightHeight();
		LightEye = LightAt + LightEye;
		SmCb.LightPos = LightEye;
		SmCb.LightPos.w = 1.0f;
		bsm::Mat4x4 LightView, LightProj;
		//���C�g�̃r���[�Ǝˉe���v�Z
		LightView = XMMatrixLookAtLH(LightEye, LightAt, bsm::Vec3(0, 1.0f, 0));
		LightProj = XMMatrixOrthographicLH(Shadowmap::GetViewWidth(), Shadowmap::GetViewHeight(),
			Shadowmap::GetLightNear(), Shadowmap::GetLightFar());
		SmCb.LightView = bsm::transpose(LightView);
		SmCb.LightProjection = bsm::transpose(LightProj);

		Mat4x4 TAView, TAProj;

		TAView = XMMatrixLookAtLH(TrickArtBase::GetDirValue(state::Right) + LightAt, LightAt, Vec3(0, 1.0f, 0));
		TAProj = XMMatrixOrthographicLH(CameraPtr->GetWidth() * 1.6f, CameraPtr->GetHeight() * 1.6f,
			CameraPtr->GetNear(), CameraPtr->GetFar());
		SmCb.TAViewR = bsm::transpose(TAView);
		TAView = XMMatrixLookAtLH(TrickArtBase::GetDirValue(state::Left) + LightAt, LightAt, Vec3(0, 1.0f, 0));
		SmCb.TAViewL = bsm::transpose(TAView);
		SmCb.TAProjection = bsm::transpose(TAProj);
	}
}
//end basecross