/*!
@file TADrawRenderTarget.h
@brief トリックアートマップのレンダリングターゲット
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class TADrawRenderTarget : public RenderTarget {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		explicit TADrawRenderTarget();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~TADrawRenderTarget();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	レンダリングターゲットビューを得る
		@return	レンダリングターゲットビューインターフェイスのポインタ
		*/
		//--------------------------------------------------------------------------------------
		ID3D11RenderTargetView* GetRenderTargetView() const;
		ID3D11ShaderResourceView* GetShaderResourceView() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デプスステンシルテクスチャを得る
		@return	デプスステンシルテクスチャインターフェイスのポインタ
		*/
		//--------------------------------------------------------------------------------------
		ID3D11Texture2D* GetDepthStencil() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デプスステンシルビューを得る
		@return	デプスステンシルビューインターフェイスのポインタ
		*/
		//--------------------------------------------------------------------------------------
		ID3D11DepthStencilView* GetDepthStencilView() const;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	レンダリングターゲットをクリアする仮想関数（スクリーン全体をクリアする）
		@param[in]	col	クリア色
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void ClearViews(const bsm::Col4& col = bsm::Col4(0, 0, 0, 1.0f)) override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	レンダリングターゲットを開始する
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void StartRenderTarget()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	レンダリングターゲットを終了する
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void EndRenderTarget()override;
	private:
		// pImplイディオム
		struct Impl;
		unique_ptr<Impl> pImpl;
	};
}
//end basecross