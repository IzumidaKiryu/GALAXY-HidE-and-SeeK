#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "TItlePlayer.h"
#include "TitleStage.h"
#include "TitleCamera.h"
#include "sound/SoundEngine.h"
#include "Fead.h"
Title::Title() {
	
}

Title::~Title() {
	if (m_gameLoopFlag == false) {
		DeleteGO(m_tlpl);
		DeleteGO(m_tlssute);
		DeleteGO(m_tlcm);
	}
	DeleteGO(m_titleBGM);
}

bool Title::Start()
{
	m_spriteRender.Init("Assets/myfaile/yattabe.DDS", 1920, 1080);
	m_GYALAXYRender.Init("Assets/myfaile/GYALAXY.DDS", 1920, 1080);
	m_GYALAXYRender.SetPosition(m_fastPos);
	m_PressRender.Init("Assets/myfaile/Press.DDS", 1920, 1080);
	m_PressRender.SetPosition(Vector3(60.0f, -640.0f, 0.0f));
	g_soundEngine->ResistWaveFileBank(1, "Assets/SoundBGMfile/title.wav");
	m_titleBGM = NewGO<SoundSource>(0, "titleBGM");
	m_titleBGM->Init(1);
	m_titleBGM->Play(true);

	SkyCube* skyCube = NewGO<SkyCube>(0, "cube");
	skyCube->SetType(enSkyCubeType_NightToon_2);
	skyCube->SetScale(1750.0f);
	if (m_gameLoopFlag == false) {
		m_tlpl = NewGO<TItlePlayer>(0, "tlpl");
		m_tlssute = NewGO<TitleStage>(0, "tlsute");
		m_tlcm = NewGO<TitleCamera>(0, "tlcm");
		m_fead = FindGO<Fead>("fead");
		
	}
	else {
		m_spriteFlag = true;
		m_fead = NewGO<Fead>(1, "fead");
	}
	
	m_fead->StartFadeIn();
	return true;
}

void Title::Update() {

	if (m_spriteFlag != true)
	{
		if (m_tlpl->m_flag == true) {

			if (!m_fead->IsFade()) {
				//フェードアウト後じゃなかったらフェードアウトを開始。
				if (!m_fead->IsInOut() == Fead::en_NowOut)
				{
					m_fead->StartFadeOut();//0->1。
				}
			}

			if (!m_fead->IsFade()) {
				m_fead->StartFadeIn();
				m_spriteFlag = true;
			}

		}
	}
	else if (m_spriteFlag == true) {
		Moziten();
		t += g_gameTime->GetFrameDeltaTime()/3.0f;
		if (t > 1.0f) {
			t = 1.0f;
			m_GyaraFlag = true;
		}
		m_vec.Lerp(t, m_fastPos, m_endPos);
	}
	

	if (m_isWaitFadeout == true) {
		if (!m_fead->IsFade()) {
			NewGO<Game>(0, "game");
			//自身を削除する。
			DeleteGO(this);
		}
	}
	else {
		//Aボタンを押したら。
		if (g_pad[0]->IsTrigger(enButtonA)&&m_GyaraFlag==true) {
			m_isWaitFadeout = true;
			m_fead->StartFadeOut();
		}
	}
	m_GYALAXYRender.SetPosition(m_vec);
	m_GYALAXYRender.Update();
	m_PressRender.Update();
}

void Title::Moziten()
{
	if (m_isWaitFadeout) {
		m_alpha += g_gameTime->GetFrameDeltaTime() * 20.2f;
	}
	else {
		m_alpha += g_gameTime->GetFrameDeltaTime() * 1.3f;
	}
	m_PressRender.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, fabsf(sinf(m_alpha))));
}


void Title::Render(RenderContext& rc){
	if (m_spriteFlag == true) {
		m_spriteRender.Draw(rc);
		m_GYALAXYRender.Draw(rc);
		m_PressRender.Draw(rc);
	}
}


