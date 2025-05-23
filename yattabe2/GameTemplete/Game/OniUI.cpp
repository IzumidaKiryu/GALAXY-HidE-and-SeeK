#include "stdafx.h"
#include "OniUI.h"
#include "Oni.h"

OniUI::OniUI() {

}

OniUI::~OniUI()
{
}

bool OniUI::Start()
{
	m_spriteRender2.Init("Assets/myfaile/midoo.DDS", 1024, 128);
	m_SpriteRender.Init("Assets/myfaile/HPBAR.DDS", 1024, 128);
	m_spriteNige.Init("Assets/myfaile/nigero.DDS", 1024, 128);
	m_oni = FindGO<Oni>("oni");
	m_SpriteRender.SetScale(Vector3(0.5f, 0.5f, 0.5f));
	m_SpriteRender.SetPosition(Vector3(640.0f, 335.0f, 0.0f));
	m_spriteRender2.SetPosition(Vector3(460.0f, 335.0f, 0.0f));
	m_spriteRender2.SetScale(Vector3(0.2f, 0.5f, 0.5f));
	m_spriteRender2.SetPivot(Vector2(0.0f, 0.5f));
	m_spriteNige.SetPosition(Vector3(100.0f, 250.0f, 0.0f));
	return true;
}

void OniUI::Update()
{
	if (m_oni->m_charaCon.IsOnGround() == true) {
		m_scalb.x += g_gameTime->GetFrameDeltaTime()*10.0f;
		m_scalb.y += g_gameTime->GetFrameDeltaTime()*10.0f;
		if (m_scalb.x >= 12.0f) {
			m_nigeFlag = true;
		}
	}

		int MaxHP = m_oni->m_OniMaxHP;
		int nawHP = m_oni->m_OniHP;
		float wari = (float)nawHP / (float)MaxHP;
		Vector3 scal = { 0.425f,0.48f,0.5f };
		scal.x *= wari;
		m_spriteRender2.SetScale(scal);
		m_spriteNige.SetScale(m_scalb);

		m_spriteRender2.Update();
		m_SpriteRender.Update();
		m_spriteNige.Update();
	
}

void OniUI::Render(RenderContext& rc)
{
	if (m_nigeFlag == false) {
		m_spriteNige.Draw(rc);
	}
	m_spriteRender2.Draw(rc);
	m_SpriteRender.Draw(rc);
	
}
