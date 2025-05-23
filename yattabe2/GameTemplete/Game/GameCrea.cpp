#include "stdafx.h"
#include "GameCrea.h"
#include "Title.h"
#include "Game.h"
#include "EndingCamera.h";
#include "sound/SoundEngine.h"
#include "Fead.h"

//�J�����̃C�[�W���O�ŃI�f�b�Z�C�̂悤�Ȋ����̉��o��������Q�[���N���A�̕������o���B

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
			//�t�F�[�h�A�E�g�ザ��Ȃ�������t�F�[�h�A�E�g���J�n�B
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
		m_title=NewGO<Title>(0, "title");   //�t�F�[�h�N���X�ɂ���t�F�[�h�폜�p�̊֐����Ăяo���폜������B
		m_title->m_gameLoopFlag = true;
		m_fead->StartFadeOut();
		m_fead->DeleteFead();
		m_game->DeleteGame();

	    //�������Ȃ��ƕ`�悪�^�C�g���̂ق���ƂȂ�Fead�������Ȃ��Ȃ�B�Q�[���I�[�o�[�ł������������B
	}
	m_mozi.Update();
}

void GameCrea::Render(RenderContext& rc)
{
	if (m_spriteFlag == true) {
		m_mozi.Draw(rc);
	}
}
