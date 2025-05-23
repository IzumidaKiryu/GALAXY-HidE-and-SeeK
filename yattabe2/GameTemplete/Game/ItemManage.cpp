#include "stdafx.h"
#include "ItemManage.h"
#include "Player.h"
#include "sound/SoundEngine.h"

ItemManage::ItemManage() {

}

ItemManage::~ItemManage()
{
	DeleteGO(m_bgm);
	DeleteGO(m_bgm2);
}

bool ItemManage::Start()
{
	m_player = FindGO<Player>("player");
	g_soundEngine->ResistWaveFileBank(5, "Assets/SoundBGMfile/sokudo.wav");
	m_bgm = NewGO<SoundSource>(0, "sokudo");
	m_bgm->Init(5);
	g_soundEngine->ResistWaveFileBank(6, "Assets/SoundBGMfile/sokudo.wav");
	m_bgm2 = NewGO<SoundSource>(0, "Sokudo2");
	m_bgm2->Init(6);
	return true;
}

void ItemManage::Update()
{
	Font();
	Sokudohennka();
}

void ItemManage::Font() {
	wchar_t wcsbuf[256];
	if (m_whatFontFlag == false) {
		swprintf_s(wcsbuf, 256, L"悲鳴の残滓を灰にしろ！！");
		//表示するテキストを設定。
		m_fontRender.SetText(wcsbuf);
		m_larpTime += g_gameTime->GetFrameDeltaTime()/2.0f;
		if (m_larpTime > 1.0f) {
			m_larpTime = 1.0f;
		}
		m_scal.Lerp(m_larpTime, m_fastScal, m_endScal);
		//フォントの位置を設定。
		m_fontRender.SetPosition(Vector3(-250.0f, 0.0f, 0.0f));

		//フォントの大きさを設定。
		m_fontRender.SetScale(m_scal.x);
		//フォントの色を設定。
		m_fontRender.SetColor(0.0f, 1.0f, 1.0f, 1.0f);
	}
	else {
		swprintf_s(wcsbuf, 256, L"Xボタン|速度UP　残り%d個", int(m_SokuSyozi));
	//表示するテキストを設定。
	m_fontRender.SetText(wcsbuf);
	//フォントの位置を設定。
	m_fontRender.SetPosition(Vector3(-920.0f, 500.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender.SetScale(1.2f);
	//フォントの色を設定。
	m_fontRender.SetColor(1.0f, 0.5f, 1.0f, 1.0f);
	}
	
}

void ItemManage::Sokudohennka() {

	if (m_SokuSyozi > 0 && g_pad[0]->IsTrigger(enButtonX)) {//Xボタン（キーボードのl）が押されたとき。
			m_UpFlag = true;
			m_SokuSyozi -= 1;
			m_player->m_BaisokuCnt += 1.0f;
			if (m_saiseiCoice == 0) {

				m_bgm->Play(false);
				m_saiseiCoice += 1;
			}
			else if (m_saiseiCoice == 1) {
				m_bgm2->Play(false);
			}
		
		
	}
	if (m_UpFlag == true) {
		m_timer += g_gameTime->GetFrameDeltaTime();
	}
	if (m_timer > 7.0f) {
		m_player->m_BaisokuCnt = 1.0f;
		m_timer = 0.0f;
		m_UpFlag = false;
	}
}

void ItemManage::Render(RenderContext& rc)
{
	m_fontRender.Draw(rc);
}

