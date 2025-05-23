#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Ground.h"
#include "PlayerCamera.h"
#include "Oni.h"
#include "Item.h"
#include "ItemSokudo.h"
#include "NokoriTime.h"
#include "GameCrea.h"
#include "GameOver.h"
#include "PlayerUI.h"
#include "OniUI.h"
#include "ItemManage.h"
#include "OniCamera.h"
#include "Map.h"
#include "Fead.h"


Game::Game()
{
}

Game::~Game()
{
	if (m_ceaOrOverFlag == true) {
		DeleteGO(m_crea);
	}
	else {
		DeleteGO(m_gameOver);
	}
	DeleteGO(m_item);
	DeleteGO(m_itemsoku);
	DeleteGO(m_itemsoku2);
	DeleteGO(m_time);
	DeleteGO(m_plcamera);
	///
	
	DeleteGO(m_ground);
	DeleteGO(m_player);
	DeleteGO(m_cube);

}

void Game::InitOnifromPlayerCamera()
{
	m_plcamera = NewGO<PlayerCamera>(0, "plcame");//プレイヤーカメラの生成。
	
}

void Game::InitUI()
{
	m_time = NewGO<NokoriTime>(0, "time");//時間クラスの生成。
	m_oniUI = NewGO<OniUI>(0, "oniUI");//鬼のUIの生成。
	m_playerUI = NewGO<PlayerUI>(0, "playerUI");//プレイヤーのUIの生成。
	m_map = NewGO<Map>(0, "map");
	m_IMana->m_whatFontFlag = true;
}

void Game::DeleteUI()
{
	DeleteGO(m_oniUI);
	DeleteGO(m_playerUI);
	DeleteGO(m_IMana);
	DeleteGO(m_map);
	DeleteGO(m_oni);
}

void Game::DeleteGame()
{
	DeleteGO(this);
}

bool Game::Start()
{
	m_player = NewGO<Player>(0, "player");//プレイヤーの生成。

	m_ground = NewGO<Ground>(0, "groud");//ステージノ生成。
	m_IMana = NewGO<ItemManage>(0, "Mana");//アイテム管理クラスの生成。
	m_oni = NewGO<Oni>(0, "oni");        //鬼の生成。
	m_item = NewGO<Item>(0, "item");     //ピザの生成。
	m_itemsoku = NewGO<ItemSokudo>(0, "itemsoku");//速度UPドリンクの生成。
	m_itemsoku2 = NewGO<ItemSokudo>(0, "itemsoku");
	m_itemsoku2->m_position = { 1900.0f,0.0f,120.0f };
	m_onikame = NewGO<OniCamera>(0, "onikame");//鬼の降臨時のカメラ。
	m_cube = FindGO<SkyCube>("cube");
	m_fead = FindGO<Fead>("fead");
	m_fead->StartFadeIn();
	return true;
}

void Game::Update()
{
	if (m_time != nullptr) {///NEWGOフラグをなくせるようにクリアを出す前にカメライージングを呼ぶ。
		if ( m_CreaFlag == true && m_NewGOFlag == false) {
			m_crea = NewGO<GameCrea>(0, "crea");
			m_NewGOFlag = true;
			m_time->m_onRenderFlag = false;
			DeleteUI();
			m_player->m_bgm->Stop();
			return;
		}

		else if (m_player->m_playerHP <= 0 && m_NewGOFlag == false) {
			m_gameOver=NewGO<GameOver>(0, "gameover");
			m_ceaOrOverFlag = false;
			m_NewGOFlag = true;
			m_time->m_onRenderFlag = false;
			DeleteUI();
			m_fead->StartFadeOut();
			m_player->m_bgm->Stop();
			return;
		}
	}
}

void Game::Render(RenderContext& rc)
{
}