#include "stdafx.h"
#include "PlayerUI.h"
#include "Player.h"

PlayerUI::PlayerUI()
{
	
}


PlayerUI::~PlayerUI()
{
}	

bool PlayerUI::Start()
{
	m_spriteRender2.Init("Assets/myfaile/midoo.DDS", 1024, 128);
	m_SpriteRender.Init("Assets/myfaile/HPBAR.DDS", 1024, 128);//画像の白いとこを消す
	m_player = FindGO<Player>("player");
	m_SpriteRender.SetScale(Vector3(0.5f, 0.5f, 0.5f));
	m_SpriteRender.SetPosition(Vector3(-640.0f, -335.0f, 0.0f));
	m_spriteRender2.SetPosition(Vector3(-820.0f, -335.0f, 0.0f));
	m_spriteRender2.SetScale(Vector3(0.2f, 0.5f, 0.5f));
	m_spriteRender2.SetPivot(Vector2(0.0f, 0.5f));
	return true;
}

void PlayerUI::Update()
{
	//Rayの動作確認用の突貫のHP表示
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"プレイヤーのHP");
	//表示するテキストを設定。
	m_fontRender.SetText(wcsbuf);
	//フォントの位置を設定。
	m_fontRender.SetPosition(Vector3(-840.0f, -400.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender.SetScale(1.0f);
	//フォントの色を設定。
	m_fontRender.SetColor(g_vec4Yellow);

	int MaxHP = m_player->m_maxHP;
	int nawHP = m_player->m_playerHP;
	float wari = (float)nawHP / (float)MaxHP;
	Vector3 scal = { 0.425f,0.4f,0.5f };
	scal.x *= wari;
	m_spriteRender2.SetScale(scal);
	m_spriteRender2.Update();
	m_SpriteRender.Update();
}

void PlayerUI::Render(RenderContext& rc)
{
	m_fontRender.Draw(rc);
	m_spriteRender2.Draw(rc);
	m_SpriteRender.Draw(rc);

}
