#include "stdafx.h"
#include "ItemSokudo.h"
#include "Player.h"
#include "ItemManage.h"
#include "sound/SoundEngine.h"


ItemSokudo::ItemSokudo()
{

	
}

ItemSokudo::~ItemSokudo()
{
	DeleteGO(m_bgm);
}

bool ItemSokudo::Start()
{
	m_modelRender.Init("Assets/MrYoshinagaPresentsAssets/Food/Drink_01.tkm");
	srand(time(nullptr));
	m_sokupox = rand() % 6000 - 3000;//座標をランダムに設定する。
	m_sokupoz = rand() % 6000 - 3000;
	m_position = { (float)m_sokupox,0.0f,(float)m_sokupoz };
	m_modelRender.SetScale(30.0f, 30.0f, 30.0f);
	m_player = FindGO<Player>("player");
	m_Imana = FindGO<ItemManage>("Mana");//	FindGOで間違ってる->コンストラクタ実行された後にマネジがNewGOされてたから。
	g_soundEngine->ResistWaveFileBank(4, "Assets/SoundBGMfile/syutoku.wav");
	m_bgm = NewGO<SoundSource>(0, "syutokuonn");
	m_bgm->Init(4);
	return true;
}

void ItemSokudo::Update()
{
	Vector3 diff = m_position - m_player->m_position;
	if (diff.Length() <= 60.0f) {
		m_count = 1;
		m_bgm->Play(false);
	}
	if (m_count == 1) {
		m_groundtime += g_gameTime->GetFrameDeltaTime();
	}
	
	if (m_groundtime >= 0.7f) {
		m_count = 0;
		m_Imana->m_SokuSyozi += 1;
		DeleteGO(this);
	}
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void ItemSokudo::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

