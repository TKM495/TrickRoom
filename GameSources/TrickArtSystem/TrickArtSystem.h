#pragma once
#include "stdafx.h"
#include "TrickArtBase.h"
#include "TrickArtDraw.h"
#include "PNTStaticDraw2.h"
#include "TADrawRenderTarget.h"

//外部シンボルは～未解決です。のエラーが出るので解決するまで使用しない
//namespace basecross {
//	static class TrickArtSystem{
//		static shared_ptr<TADrawRenderTarget> m_TADrawRenderTargets[(int)TADirection::MAX];;
//	public:
//		static shared_ptr<TADrawRenderTarget> GetTADrawRenderTarget(TADirection dir) {
//			if (!m_TADrawRenderTargets[(int)dir]) {
//				m_TADrawRenderTargets[(int)dir] = make_shared<TADrawRenderTarget>();
//			}
//			return m_TADrawRenderTargets[(int)dir];
//		}
//		static shared_ptr<TADrawRenderTarget> GetTADrawRenderTarget(int num) {
//			if (!m_TADrawRenderTargets[num]) {
//				m_TADrawRenderTargets[num] = make_shared<TADrawRenderTarget>();
//			}
//			return m_TADrawRenderTargets[num];
//		}
//	};
//}