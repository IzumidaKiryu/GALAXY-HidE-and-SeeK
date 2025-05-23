#include "stdafx.h"
#include "GameOver.h"
#include "Title.h"
#include "Game.h"
#include "sound/SoundEngine.h"
#include "Fead.h"

GameOver::GameOver() {
	
}

GameOver::~GameOver()
{
	DeleteGO(m_bgm);
}

bool GameOver::Start()
{
	m_spriteRender.Init("Assets/myfaile/EndGame2.DDS", 1920, 1080);
	g_soundEngine->ResistWaveFileBank(8, "Assets/SoundBGMfile/badEndhig.wav");
	m_bgm = NewGO<SoundSource>(0, "OverBgM");
	m_bgm->Init(8);
	m_bgm->Play(true);

	m_game = FindGO<Game>("game");
	m_fead = FindGO<Fead>("fead");
	return true;
}

void GameOver::Update()
{
	if (m_spriteFlag != true) {

		//�t�F�[�h�A�E�g�ザ��Ȃ�������t�F�[�h�A�E�g���J�n�B
		if (!m_fead->IsInOut() == Fead::en_NowOut)
		{
			m_fead->StartFadeOut();
		}
		if (!m_fead->IsFade()) {
			m_fead->StartFadeIn();//
			m_spriteFlag = true;
		}
	}
	else if (m_spriteFlag == true) {
		t += g_gameTime->GetFrameDeltaTime() / 3.0f;
		if (t > 1.0f) {
			t = 1.0f;
		}
		m_alpha += g_gameTime->GetFrameDeltaTime() * 1.2f;
	}

	if (g_pad[0]->IsTrigger(enButtonA) && m_spriteFlag == true) {

		m_title = NewGO<Title>(0, "title");   //�t�F�[�h�N���X�ɂ���t�F�[�h�폜�p�̊֐����Ăяo���폜������  �^�C�g����NewGO�̂��ƂɍēxNewGO����B
		m_title->m_gameLoopFlag = true;
		m_fead->StartFadeOut();
		m_fead->DeleteFead();
		m_game->DeleteGame();
	}
	m_spriteRender.Update();
}

void GameOver::Render(RenderContext& rc)
{
	if (m_spriteFlag == true) {
		m_spriteRender.Draw(rc);
	}
}
