/*!
@file Project.h
@brief コンテンツ用のヘッダをまとめる
*/

#pragma once

//メイン
#include "Scene.h"
#include "MainCamera.h"
#include "Player.h"
#include "CSVLoad.h"
#include "Debug.h"
#include "AdvCollision.h"
#include "MyMath.h"
#include "Utility.h"
//ステージ関係
#include "TitleStage.h"
#include "SelectStage.h"
#include "GameStage.h"
#include "ResultStage.h"
//メニュー
#include "TitleModel.h"
#include "StringSprite2.h"
#include "BaseMenu.h"
#include "TitleMenu.h"
#include "PauceMenu.h"
#include "ResultMenu.h"
#include "SelectStageMenu.h"
#include "Cursor.h"
//UI関係
#include "Numbers.h"
#include "Dot1x1.h"
#include "FrameSprite.h"
#include "BGSprite.h"
#include "ColorOut.h"
#include "ImageSprite.h"
#include "PictureFrame.h"
#include "UI_HP.h"
#include "UI_Crystal.h"
#include "Fade.h"
#include "Result.h"
#include "UI_Player.h"
#include "UI_Goalgauge.h"
#include "UI_FPS.h"
#include "UI_Rank.h"
#include "UI_LR.h"
#include "StartCountdown.h"
#include "Pause.h"
//行動やコンポーネント
#include "SinCurve.h"
#include "SquareMove.h"
#include "CircularMove.h"
#include "LinearMove.h"
#include "FadeComponent.h"
//エフェクト
#include "Effect.h"
//ステージオブジェクト
#include "StageObject.h"
#include "StageParent.h"
#include "EmptyObject.h"
#include "pursuer.h"
#include "Picture.h"
#include "Block2.h"
#include "Plane.h"
#include "Spikes.h"
#include "Enemy.h"
#include "Stairs.h"
#include "Pillar.h"
#include "Pole.h"
#include "Crystal.h"
#include "Goal.h"
//トリックアートオブジェクト
#include "TrickArtSystem/TrickArtSystem.h"
#include "TrickArtBaseOld.h"
#include "SpikesArt.h"
#include "BlockArt.h"
#include "EnemyArt.h"
#include "StairsArt.h"
#include "FloorArt.h"
#include "PoleArt.h"

//未使用
#include "FloorGenerator.h"
#include "Timer.h"
#include "StageLoad.h"
#include "Score.h"
#include "EnemyMove.h"