#include "stdafx.h"
#include "GameCrea.h"
#include "Title.h"
#include "Game.h"
#include "EndingCamera.h";
#include "sound/SoundEngine.h"
#include "Fead.h"

//カメラのイージングでオデッセイのような感じの演出をした後ゲームクリアの文字を出す。

GameCrea::GameCrea()
{
	
}

GameCrea::~GameCrea()
{
	DeleteGO(m_edCamera);
	DeleteGO(m_bgm);
}

bool GameCrea::Start()
{
	m_mozi.Init("Assets/myfaile/Crea.DDS", 1920, 1080);
	g_soundEngine->ResistWaveFileBank(9, "Assets/SoundBGMfile/CreaBGM.wav");
	m_bgm = NewGO<SoundSource>(0, "CreaBGM");
	m_bgm->Init(9);
	m_bgm->Play(true);

	m_edCamera = NewGO<EndingCamera>(0, "edcame");
	m_game = FindGO<Game>("game");
	m_fead = FindGO<Fead>("fead");
	return true;
}

void GameCrea::Update()
{
	if (m_spriteFlag != true) {
		if (m_edCamera->m_endEagingFlag == true) {
			//フェードアウト後じゃなかったらフェードアウトを開始。
			if (!m_fead->IsInOut() == Fead::en_NowOut)
			{
				m_fead->StartFadeOut();
			}
			if (!m_fead->IsFade()) {
				m_fead->StartFadeIn();
				m_spriteFlag = true;
			}
		}
	}
	else if (m_spriteFlag == true) {
		m_alpha += g_gameTime->GetFrameDeltaTime() * 1.2f;
		m_mozi.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, fabsf(sinf(m_alpha))));
	}

	if (g_pad[0]->IsTrigger(enButtonA)&&m_spriteFlag==true) {
		m_title=NewGO<Title>(0, "title");   //フェードクラスにあるフェード削除用の関数を呼び出し削除した後。
		m_title->m_gameLoopFlag = true;
		m_fead->StartFadeOut();
		m_fead->DeleteFead();
		m_game->DeleteGame();

	    //こうしないと描画がタイトルのほが上となりFeadが見えなくなる。ゲームオーバーでも同じ処理を。
	}
	m_mozi.Update();
}

void GameCrea::Render(RenderContext& rc)
{
	if (m_spriteFlag == true) {
		m_mozi.Draw(rc);
	}
}
