/*!
@file PNTStaticDraw2.cpp
@brief トリックアート描画に対応したシェーダー実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	IMPLEMENT_DX11_CONSTANT_BUFFER(CBPNTStaticDraw2Title)
	IMPLEMENT_DX11_VERTEX_SHADER(VSPNTStaticDraw2Title, App::GetApp()->GetShadersPath() + L"VSPNTStaticDraw2Title.cso")
	IMPLEMENT_DX11_PIXEL_SHADER(PSPNTStaticDraw2Title, App::GetApp()->GetShadersPath() + L"PSPNTStaticDraw2Title.cso")

	struct PNTStaticDraw2Title::Impl :public DrawObjectBase {
		//頂点変更する場合のメッシュ（オリジナル）
		shared_ptr<MeshResource> m_OriginalMeshResource;
		//オリジナルメッシュを使うかどうか
		bool m_UseOriginalMeshResource;
		///テクスチャリソース
		weak_ptr<TextureResource> m_TextureResource;
		///エミッシブ色
		bsm::Col4 m_Emissive;
		/// デフューズ色
		bsm::Col4 m_Diffuse;
		/// スペキュラー色
		bsm::Col4 m_Specular;
		///影を投影するかどうか
		bool m_OwnShadowActive;
		//モデルに入っているDiffuseを使うかどうか
		bool m_ModelDiffusePriority;
		//モデルに入っているEmissiveを使うかどうか
		bool m_ModelEmissivePriority;
		//モデルに入っているテクスチャを使うかどうか
		bool m_ModelTextureEnabled;
		///Instance描画用
		///Instance最大値
		size_t m_MaxInstance;
		/// 行列用の頂点バッファ
		ComPtr<ID3D11Buffer> m_MatrixBuffer;
		///行列の配列
		vector<bsm::Mat4x4> m_MatrixVec;
		//行列を自動クリアするかどうか
		bool m_AutoClearMatrixVec;
		PNTStaticDraw2Title::Impl() :
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


	PNTStaticDraw2Title::PNTStaticDraw2Title(const shared_ptr<GameObject>& GameObjectPtr)
		:SmBaseDraw(GameObjectPtr), pImpl(new Impl())
	{}
	PNTStaticDraw2Title::~PNTStaticDraw2Title() {}

	void PNTStaticDraw2Title::OnCreate() {
		//ライティングのみだと極端になるので調整
		SetEmissive(bsm::Col4(0.5f, 0.5f, 0.5f, 0.0f));
		SetDiffuse(bsm::Col4(0.6f, 0.6f, 0.6f, 1.0f));
	}

	void PNTStaticDraw2Title::OnDraw() {
		if (GetGameObject()->GetAlphaActive()) {
			if (!(GetBlendState() == BlendState::AlphaBlend || GetBlendState() == BlendState::Additive)) {
				SetBlendState(BlendState::AlphaBlend);
			}
			SetRasterizerState(RasterizerState::DoubleDraw);
		}
		//メッシュリソースの取得
		auto PtrMeshResource = GetMeshResource();
		if (PtrMeshResource) {
			DrawStatic2(PtrMeshResource->GetMashData());
		}
		//後始末
		auto Dev = App::GetApp()->GetDeviceResources();
		Dev->InitializeStates();

	}

	void PNTStaticDraw2Title::DrawStatic2(const MeshPrimData& data) {
		auto Dev = App::GetApp()->GetDeviceResources();
		auto pD3D11DeviceContext = Dev->GetD3DDeviceContext();
		auto RenderState = Dev->GetRenderState();
		auto scene = App::GetApp()->GetScene<Scene>();
		//NULLのシェーダリソースの準備
		ID3D11ShaderResourceView* pNull[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT] = { nullptr };
		//サンプラーの準備
		ID3D11SamplerState* pNullSR[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT] = { nullptr };
		//各オブジェクト共通処理
		//シェーダの設定
		//頂点シェーダ
		pD3D11DeviceContext->VSSetShader(VSPNTStaticDraw2Title::GetPtr()->GetShader(), nullptr, 0);
		//インプットレイアウトの設定
		pD3D11DeviceContext->IASetInputLayout(VSPNTStaticDraw2Title::GetPtr()->GetInputLayout());
		//ピクセルシェーダ
		pD3D11DeviceContext->PSSetShader(PSPNTStaticDraw2Title::GetPtr()->GetShader(), nullptr, 0);
		//個別処理
		SimpleConstantsEXTitle SmCb;
		//コンスタントバッファの作成
		SetConstants2(SmCb, data);
		//テクスチャ
		auto shTex = GetTextureResource();
		if (shTex) {
			//テクスチャがある
			SmCb.ActiveFlg.x = 1;
		}
		else {
			//描画コンポーネントにはテクスチャがない
			if (shTex = data.m_TextureResource.lock()) {
				//テクスチャがある
				SmCb.ActiveFlg.x = 1;
			}
			else {
				SmCb.ActiveFlg.x = 0;
			}
		}
		//コンスタントバッファの更新
		pD3D11DeviceContext->UpdateSubresource(CBPNTStaticDraw2Title::GetPtr()->GetBuffer(), 0, nullptr, &SmCb, 0, 0);
		//コンスタントバッファの設定
		ID3D11Buffer* pConstantBuffer = CBPNTStaticDraw2Title::GetPtr()->GetBuffer();
		ID3D11Buffer* pNullConstantBuffer = nullptr;
		//頂点シェーダに渡す
		pD3D11DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
		//ピクセルシェーダに渡す
		pD3D11DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);
		//ストライドとオフセット
		UINT stride = data.m_NumStride;
		UINT offset = 0;
		//描画方法のセット
		pD3D11DeviceContext->IASetPrimitiveTopology(data.m_PrimitiveTopology);
		//頂点バッファのセット
		pD3D11DeviceContext->IASetVertexBuffers(0, 1, data.m_VertexBuffer.GetAddressOf(), &stride, &offset);
		//インデックスバッファのセット
		pD3D11DeviceContext->IASetIndexBuffer(data.m_IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
		//各レンダリングステートの設定
		//ブレンドステート
		RenderState->SetBlendState(pD3D11DeviceContext, GetBlendState());
		//デプスステンシルステート
		RenderState->SetDepthStencilState(pD3D11DeviceContext, GetDepthStencilState());
		//テクスチャとサンプラー
		if (shTex) {
			pD3D11DeviceContext->PSSetShaderResources(0, 1, shTex->GetShaderResourceView().GetAddressOf());
			//サンプラーを設定
			RenderState->SetSamplerState(pD3D11DeviceContext, GetSamplerState(), 0);
		}
		else {
			//シェーダーリソースもクリア
			pD3D11DeviceContext->PSSetShaderResources(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, pNull);
			//サンプラーもクリア
			RenderState->SetSamplerAllClear(pD3D11DeviceContext);
		}
		//シャドウマップのレンダラーターゲット
		auto ShadowmapPtr = Dev->GetShadowMapRenderTarget();
		ID3D11ShaderResourceView* pShadowSRV = ShadowmapPtr->GetShaderResourceView();
		pD3D11DeviceContext->PSSetShaderResources(1, 1, &pShadowSRV);

		//TrickArtRenderTargetの取得
		shared_ptr<TADrawRenderTarget> TrickArtDraw = dynamic_pointer_cast<TitleStage>(GetStage())->GetTADraw();
		ID3D11ShaderResourceView* pTrickArtDrawSRV = TrickArtDraw->GetShaderResourceView();
		pD3D11DeviceContext->PSSetShaderResources(2, 1, &pTrickArtDrawSRV);
		//シャドウマップサンプラー
		ID3D11SamplerState* pShadowSampler = RenderState->GetComparisonLinear();
		pD3D11DeviceContext->PSSetSamplers(1, 1, &pShadowSampler);

		//ラスタライザステートと描画
		if (GetRasterizerState() == RasterizerState::DoubleDraw) {
			//透明処理用
			//ラスタライザステート(裏描画)
			pD3D11DeviceContext->RSSetState(RenderState->GetCullFront());
			//描画
			pD3D11DeviceContext->DrawIndexed(data.m_NumIndicis, 0, 0);
			//ラスタライザステート（表描画）
			pD3D11DeviceContext->RSSetState(RenderState->GetCullBack());
			//描画
			pD3D11DeviceContext->DrawIndexed(data.m_NumIndicis, 0, 0);
		}
		else {
			RenderState->SetRasterizerState(pD3D11DeviceContext, GetRasterizerState());
			//描画
			pD3D11DeviceContext->DrawIndexed(data.m_NumIndicis, 0, 0);
		}
	}

	void PNTStaticDraw2Title::SetConstants2(SimpleConstantsEXTitle& SmCb, const MeshPrimData& data) {
		//行列の定義
		auto PtrTrans = GetGameObject()->GetComponent<Transform>();
		//行列の定義
		bsm::Mat4x4 World, ViewMat, ProjMat;
		//ワールド行列の決定
		if (data.m_UseMeshToTransformMatrix) {
			World = data.m_MeshToTransformMatrix * GetMeshToTransformMatrix();
			World *= PtrTrans->GetWorldMatrix();
		}
		else {
			World = GetMeshToTransformMatrix() * PtrTrans->GetWorldMatrix();
		}
		//転置する
		World.transpose();
		//カメラを得る
		auto CameraPtr = GetGameObject()->OnGetDrawCamera();
		//ビューと射影行列を得る
		ViewMat = CameraPtr->GetViewMatrix();
		//転置する
		ViewMat.transpose();
		//転置する
		ProjMat = CameraPtr->GetProjMatrix();
		ProjMat.transpose();
		SmCb.World = World;
		SmCb.View = ViewMat;
		SmCb.Projection = ProjMat;
		//エミッシブ
		SmCb.Emissive = GetEmissive();
		//デフィーズ
		SmCb.Diffuse = GetDiffuse();
		//スペキュラー
		SmCb.Specular = GetSpecular();
		//ライティング
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
		//ライトのビューと射影を計算
		LightView = XMMatrixLookAtLH(LightEye, LightAt, bsm::Vec3(0, 1.0f, 0));
		LightProj = XMMatrixOrthographicLH(Shadowmap::GetViewWidth(), Shadowmap::GetViewHeight(),
			Shadowmap::GetLightNear(), Shadowmap::GetLightFar());
		SmCb.LightView = bsm::transpose(LightView);
		SmCb.LightProjection = bsm::transpose(LightProj);

		Mat4x4 TAView, TAProj;
		TAView = XMMatrixLookAtLH(Vec3(0.0f, 1.8f, -5.0f), LightAt, Vec3(0, 1.0f, 0));
		if (CameraPtr->GetPers()) {
			TAProj = XMMatrixPerspectiveFovLH(CameraPtr->GetFovY(), CameraPtr->GetAspect(),
				CameraPtr->GetNear(), CameraPtr->GetFar());
		}
		else {
			TAProj = XMMatrixOrthographicLH(CameraPtr->GetWidth(), CameraPtr->GetHeight(),
				CameraPtr->GetNear(), CameraPtr->GetFar());
		}
		SmCb.TAView = bsm::transpose(TAView);
		SmCb.TAProjection = bsm::transpose(TAProj);
	}
}
//end basecross