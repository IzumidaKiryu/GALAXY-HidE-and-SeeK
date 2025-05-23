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
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));
	//////////////////////////////////////
	// �������珉�������s���R�[�h���L�q����B
	//////////////////////////////////////
	// 
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();//�����蔻��̉����B
	//NewGO<Game>(0, "game");
	////Game�N���X�̃I�u�W�F�N�g���쐬�B
	NewGO<Title>(0, "title");
	NewGO<Fead>(1, "fead");
	
	


	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂ŁI�I�I�B
	//////////////////////////////////////
	
	// ��������Q�[�����[�v�B
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

