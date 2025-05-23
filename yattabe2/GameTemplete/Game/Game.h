#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class Ground;
class PlayerCamera;
class Oni;
class Item;
class ItemSokudo;
class NokoriTime;
class PlayerUI;
class OniUI;
class ItemManage;
class OniCamera;
class GameCrea;
class GameOver;
class Map;
class Fead;



class Game : public IGameObject
{
public:
	Game();
	~Game();
	
	//playercamera�̐����p�֐��i�O����Ăяo����悤�ɂ��邱�ƂŊǗ���Game���łł���悤�ɂ���j�B
	void InitOnifromPlayerCamera();
	void InitUI();
	void DeleteUI();
	void DeleteGame();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	bool m_CreaFlag = false;
	bool m_NewGOFlag = false;
	bool m_ceaOrOverFlag = true;//true���N���A�B

	Player* m_player=nullptr;
	Ground* m_ground=nullptr;
	PlayerCamera* m_plcamera=nullptr;
	Oni* m_oni=nullptr;
	Item* m_item=nullptr;
	NokoriTime* m_time=nullptr;
	PlayerUI* m_playerUI=nullptr;
	OniUI* m_oniUI=nullptr;
	ItemManage* m_IMana=nullptr;
	ItemSokudo* m_itemsoku = nullptr;
	ItemSokudo* m_itemsoku2 = nullptr;
	OniCamera* m_onikame=nullptr;
	GameCrea* m_crea=nullptr;
	GameOver* m_gameOver=nullptr;
	Map* m_map = nullptr;
	Fead* m_fead = nullptr;
	SkyCube* m_cube = nullptr;
	ModelRender m_modelRender;
	Vector3 m_pos = Vector3::Zero;
};

