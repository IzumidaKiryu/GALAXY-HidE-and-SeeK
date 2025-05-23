#include "stdafx.h"
#include "Fead.h"


Fead::Fead()
{

}
Fead::~Fead()
{
}

bool Fead::Start()
{
	m_spriteRender.Init("Assets/myfaile/R.DDS", 1920, 1080);
	return true;
}

void Fead::Update()
{
	switch (m_state) {
	case enState_FadeIn://•ƒJƒ‰”’B
		m_currentAlpha -= 1.0f * g_gameTime->GetFrameDeltaTime();
		if (m_currentAlpha <= 0.0f) {
			m_currentAlpha = 0.0f;
			m_state = enState_Idle;
			m_BW = en_NowIn;
		}
		break;
	case enState_FadeOut://”’‚©‚ç•B
		m_currentAlpha += 1.0f * g_gameTime->GetFrameDeltaTime();
		if (m_currentAlpha >= 1.0f) {
			m_currentAlpha = 1.0f;
			m_state = enState_Idle;
			m_BW = en_NowOut;
		}
		break;
	case enState_Idle:
		break;
	}
}

void Fead::Render(RenderContext& rc)
{
	if (m_currentAlpha > 0.0f) {
		m_spriteRender.SetMulColor({ 1.0f, 1.0f, 1.0f, m_currentAlpha });
		m_spriteRender.Draw(rc);
	}
}


void Fead::DeleteFead() {
	DeleteGO(this);
}