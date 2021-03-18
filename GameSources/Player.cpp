/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	void Player::OnCreate()
	{
		auto drawComp = AddComponent<BcPNTStaticDraw>();
		drawComp->SetMeshResource(L"DEFAULT_CUBE");

		auto transComp = GetComponent<Transform>(); // トランスフォーム(行列変換)コンポーネントを取得
		transComp->SetRotation(0, XMConvertToRadians(0), 0);


		AddComponent<Gravity>();
		AddComponent<CollisionObb>();
	}

	void Player::SetSpeed()
	{
		auto& app = App::GetApp();
		float ElapsedTime = app->GetElapsedTime();
		auto cntlPad = app->GetInputDevice().GetControlerVec();//コントローラーの取得

		float fThumbLY = 0.0f;
		float fThumbLX = 0.0f;
		if (cntlPad[0].bConnected)
		{
			fThumbLY = cntlPad[0].fThumbLY;
			fThumbLX = cntlPad[0].fThumbLX;
		}

		if (fThumbLX != 0 || fThumbLY != 0)
		{
			//コントローラの向き
			float moveX = fThumbLX;
			float moveZ = fThumbLY;
			Vec2 moveVec(moveZ, moveX);
			float moveSize = moveVec.length();
			moveSize *= ElapsedTime * 5.0f;

			////Playerの向き
			//float MoveDirectionX = fThumbLX;
			//float MoveDirectionY = fThumbLY;

			//auto transComp = GetComponent<Transform>();
			//auto quat = transComp->GetQuaternion();
			//auto rot = quat.toRotVec(); //軸ごとの回転にする

			//rot.y = atan2f(-MoveDirectionY, MoveDirectionX) + XM_PIDIV2; 
			//transComp->SetRotation(0, rot.y, 0);

			//角度
			float cntlAngle = atan2(moveZ, moveX);
			//ベクトル作成
			m_Speed = Vec3(cos(cntlAngle), 0, sin(cntlAngle));
			//正規化する
			m_Speed.normalize();
			//移動サイズを設定
			m_Speed *= moveSize;

			m_Speed.y = 0;
		}

		else
		{
			m_Speed = Vec3(0.0f);
		}

	}

	void Player::OnUpdate()
	{
		SetSpeed();

		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();
		pos += m_Speed;

		auto stage = GetStage(); // ステージを取得

		transComp->SetPosition(pos); // 更新した座標をTransformに設定

		//Playerの向き
		if (m_Speed.length() > 0.0f)
		{
			auto utilPtr = GetBehavior<UtilBehavior>();
			utilPtr->RotToHead(m_Speed, 1.0f);
		}

		//m_InputHandler.PushHandle(GetThis<Player>());

	}

	//void Player::OnPushA()
	//{


	//	//SetGravityVerocityを取得して、SetGravityVerocityのSpeedが0になったら地面と接触していると見なして、フラグを倒す
	//	if (bJump == false)
	//	{
	//		bJump = true;
	//		auto GravityComp = GetComponent<Gravity>();
	//		GravityComp->SetGravityVerocity(Vec3(0, 5, 0));

	//	}

	//	if ()
	//	{
	//		auto GravityComp = GetComponent<Gravity>();
	//		GravityComp->GetGravityVelocity();

	//	}

	//}


	void Player::SetHP(int HP)
	{
		m_HP = HP;
	}

	int Player::GetHP()
	{
		return m_HP;
	}



}
//end basecross

