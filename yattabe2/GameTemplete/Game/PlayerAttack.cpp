#include "stdafx.h"
#include "PlayerAttack.h"
#include "Player.h"
#include "Oni.h"
#include "NokoriTime.h"
#include "collision/CollisionObject.h"
#include "graphics/effect/EffectEmitter.h"
#include "sound/SoundEngine.h"

PlayerAttack::PlayerAttack()
{
	
}

PlayerAttack::~PlayerAttack()
{
	//エフェクトの再生を停止する。
	m_effectEmitter->Stop();
	//色々削除。
	DeleteGO(m_effectEmitter);
	DeleteGO(m_coll);
	DeleteGO(m_bgm);
}

bool PlayerAttack::Start() {
	g_soundEngine->ResistWaveFileBank(2, "Assets/SoundBGMfile/fireball.wav");
	m_bgm = NewGO<SoundSource>(0, "fireBall");
	m_bgm->Init(2);
	m_bgm->Play(true);

	m_player = FindGO<Player>("player");
	m_oni = FindGO<Oni>("oni");
	m_time = FindGO<NokoriTime>("time");
	//エフェクトを読み込む。
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/efk/magic_fire.efk");
	//ここにエフェクトのパスを入れる

	//エフェクトのオブジェクトを作成する。
	m_effectEmitter = NewGO <EffectEmitter>(0);
	m_effectEmitter->Init(0);
	//エフェクトの大きさを設定する。
	m_effectEmitter->SetScale(m_scale * 30.0f);
	//移動速度を計算。
	m_position.y += 50.0f;
	m_moveSpeed = Vector3::AxisZ;
	m_rotation.Apply(m_moveSpeed);
	m_position += m_moveSpeed * 50.0f;
	m_moveSpeed *= 1200.0f;
	m_rotation.AddRotationDegY(360.0f);
	//回転を設定する。
	m_effectEmitter->SetRotation(m_rotation);
	m_effectEmitter->Play();

	//コリジョンオブジェクトを作成する。
	m_coll = NewGO<CollisionObject>(0);
	//球状のコリジョンを作成する。
	m_coll->CreateSphere(m_position, Quaternion::Identity, 35.0f * m_scale.z);

	//名前をplayer_fireballにする。
	m_coll->SetName("player_fireball");

	//コリジョンオブジェクトが自動で削除されないようにする。
	m_coll->SetIsEnableAutoDelete(false);

	return true;
}

void PlayerAttack::Update()
{
//タイマーを加算する。
	m_timer += g_gameTime->GetFrameDeltaTime();
	
	if (m_timer > 1.0f) {
		//座標を移動させる。
		m_position += m_moveSpeed * g_gameTime->GetFrameDeltaTime();
		
	}
	else {
		m_position = m_player->m_position;
		m_position.y += 50.0f;
	}
	
//エフェクトの座標を設定する。
		m_effectEmitter->SetPosition(m_position);
		//コリジョンオブジェクトに座標を設定する。
		m_coll->SetPosition(m_position);

 	

	//タイマーが3.0f以上だったら。
	 if (m_timer >= 3.0f)
	{
		m_player->m_ballView = false;
		//自身を削除する。
		DeleteGO(this);
	}
}