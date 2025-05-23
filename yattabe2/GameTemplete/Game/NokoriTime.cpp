#include "stdafx.h"
#include "NokoriTime.h"
#include "Player.h"
#include "Game.h"

NokoriTime::NokoriTime()
{
	
}

NokoriTime::~NokoriTime()
{

}

bool NokoriTime::Start() {
	m_player = FindGO<Player>("player");
	m_game = FindGO<Game>("game");
	return true;
}

void NokoriTime::Update()
{
	if (m_player->m_position.y > 120.0f) {
		return;
	}
	else
	{
		m_timer -= g_gameTime->GetFrameDeltaTime();
	}
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"残り時間%d秒",(int)(m_timer));
	//表示するテキストを設定。
	m_fontRender.SetText(wcsbuf);
	//フォントの位置を設定。
	m_fontRender.SetPosition(Vector3(-160.0f, 500.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender.SetScale(1.2f);
	//フォントの色を設定。
	m_fontRender.SetColor(g_vec4Yellow);

	if (m_timer < 30.0f) {
		m_fontRender.SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	}
	if (m_timer <= 0.0f) {
		m_timer = 0.0f;
		m_game->m_CreaFlag = true;
	}
}

void NokoriTime::Render(RenderContext& rc)
{
	if (m_onRenderFlag == true) {
		m_fontRender.Draw(rc);
	}	
}





