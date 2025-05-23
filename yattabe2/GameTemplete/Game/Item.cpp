#include "stdafx.h"
#include "Item.h"
#include "Player.h"
#include "time.h"
#include "sound/SoundEngine.h"

Item::Item() {

}

Item::~Item() {
	DeleteGO(m_bgm);
}

bool Item::Start()
{
	m_modelRender.Init("Assets/MrYoshinagaPresentsAssets/Food/Pizza.tkm");
	srand(time(nullptr));
	m_pox = rand() % 12000 - 6000;//ピザの座標をランダムに設定する。
	m_poz = rand() % 12000 - 6000;
	m_position = { (float)m_pox,0.0f,(float)m_poz };
	m_modelRender.SetScale(70.0f, 70.0f, 70.0f);
	m_player = FindGO<Player>("player");
	g_soundEngine->ResistWaveFileBank(7, "Assets/SoundBGMfile/kou.wav");
	m_bgm = NewGO<SoundSource>(0, "PizaGM");
	m_bgm->Init(7);
	return true;
}

void Item::Update() {
	Vector3 diff = m_position - m_player->m_position;
	if (diff.Length() <= 120.0f) {
		m_player->m_playerATK = 2;
		m_count = 1;
		m_bgm->Play(false);
	}
	if (m_count == 1) {
		m_groundtime += g_gameTime->GetFrameDeltaTime();
	}

	if (m_groundtime > 0.2f) {
		DeleteGO(this);
	}
	//エフェクトの座標を設定する。
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void Item::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}