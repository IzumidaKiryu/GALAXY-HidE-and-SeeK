#include "stdafx.h"
#include "system/system.h"

#include<InitGUID.h>
#include<dxgidebug.h>

#include "Title.h"
#include "Fead.h"
#include "Game.h"



void ReportLiveObjects()
{
	
}

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));
	//////////////////////////////////////
	// ここから初期化を行うコードを記述する。
	//////////////////////////////////////
	// 
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();//当たり判定の可視化。
	//NewGO<Game>(0, "game");
	////Gameクラスのオブジェクトを作成。
	NewGO<Title>(0, "title");
	NewGO<Fead>(1, "fead");
	
	


	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！。
	//////////////////////////////////////
	
	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		if (g_pad[0]->IsTrigger(enButtonA) ){
			g_pad[0]->SetVibration(/*durationSec=*/0.5f, /*normalizedPower=*/1.0f);
		}
		K2Engine::GetInstance()->Execute();
	}

	K2Engine::DeleteInstance();

#ifdef _DEBUG
	ReportLiveObjects();
#endif // _DEBUG
	return 0;
}

