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
	m_SpriteRender.Init("Assets/myfaile/HPBAR.DDS", 1024, 128);//�摜�̔����Ƃ�������
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
	//Ray�̓���m�F�p�̓ˊт�HP�\��
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"�v���C���[��HP");
	//�\������e�L�X�g��ݒ�B
	m_fontRender.SetText(wcsbuf);
	//�t�H���g�̈ʒu��ݒ�B
	m_fontRender.SetPosition(Vector3(-840.0f, -400.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
	m_fontRender.SetScale(1.0f);
	//�t�H���g�̐F��ݒ�B
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
