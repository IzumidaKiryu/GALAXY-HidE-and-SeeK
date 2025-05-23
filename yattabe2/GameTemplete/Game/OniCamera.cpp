#include "stdafx.h"
#include "OniCamera.h"
#include "Oni.h"
#include "Player.h"
#include "Game.h"

OniCamera::OniCamera()
{
}

OniCamera::~OniCamera()
{
}

bool OniCamera::Start()
{
	//プレイヤーのインスタンスを探す。
	m_player = FindGO<Player>("player");
	m_oni = FindGO<Oni>("oni");
	m_game = FindGO<Game>("game");

	//注視点から視点までのベクトルを設定。
	//m_toCameraPos.Set(0.0f, 125.0f, -600.0f);//ここ指定した値分ターゲットから離れるようになる。
	//視点と注してんんが一緒になるとエラーが起きる。Unityちゃんの座標が０００なので一緒になってしまったのが原因。
	m_toCameraPos.Set(0.0f, -1800.0f, -255.0f);

	//カメラのニアクリップとファークリップを設定する。
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(30000.0f);

	return true;
}

void OniCamera::Update()
{
	//カメラを更新。
	//注視点を計算する。
	Vector3 target = m_oni->m_position;
	//プレイヤの足元からちょっと上を注視点とする。
	target.y += 80.0f;
	Vector3 toCameraPosOld = m_toCameraPos;
	
	//視点を計算する。
	Vector3 pos = target + m_toCameraPos;	
	
	//メインカメラに注視点と視点を設定する。
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);
	if (m_oni->m_charaCon.IsOnGround()) {
		posy = 150.0f;
		m_time+= g_gameTime->GetFrameDeltaTime();
	}
	m_toCameraPos.Set(0.0f,posy , -700.0f);
	if (m_time >= 0.5f) {
		m_time = 0.0f;
		m_game->InitOnifromPlayerCamera();
		m_game->InitUI();
		DeleteGO(this);
	}
	//カメラの更新。
	g_camera3D->Update();
}
