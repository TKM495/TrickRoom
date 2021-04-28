#pragma once
#include "stdafx.h"
#include "TrickArtBase.h"
#include "TrickArtDraw.h"
#include "PNTStaticDraw2.h"
#include "TADrawRenderTarget.h"

//外部シンボルは～未解決です。のエラーが出るので解決するまで使用しない
//namespace basecross {
//	class TrickArtSystem{
//		static shared_ptr<TADrawRenderTarget> m_TADrawRenderTargets[2];
//		static TrickArtSystem* s_instance;
//		TrickArtSystem()
//		{
//			s_instance = NULL;
//		}
//	public:
//		static TrickArtSystem* GetInstance() {
//			return s_instance;
//		}
//
//		static void Create() {
//			if (!s_instance)
//			{
//				s_instance = new TrickArtSystem;
//			}
//		}
//
//		static void Destroy() {
//			delete s_instance;
//			s_instance = NULL;
//		}
//		static shared_ptr<TADrawRenderTarget> GetTADrawRenderTarget(state dir) {
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