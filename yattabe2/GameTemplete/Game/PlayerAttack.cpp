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
	//�G�t�F�N�g�̍Đ����~����B
	m_effectEmitter->Stop();
	//�F�X�폜�B
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
	//�G�t�F�N�g��ǂݍ��ށB
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/efk/magic_fire.efk");
	//�����ɃG�t�F�N�g�̃p�X������

	//�G�t�F�N�g�̃I�u�W�F�N�g���쐬����B
	m_effectEmitter = NewGO <EffectEmitter>(0);
	m_effectEmitter->Init(0);
	//�G�t�F�N�g�̑傫����ݒ肷��B
	m_effectEmitter->SetScale(m_scale * 30.0f);
	//�ړ����x���v�Z�B
	m_position.y += 50.0f;
	m_moveSpeed = Vector3::AxisZ;
	m_rotation.Apply(m_moveSpeed);
	m_position += m_moveSpeed * 50.0f;
	m_moveSpeed *= 1200.0f;
	m_rotation.AddRotationDegY(360.0f);
	//��]��ݒ肷��B
	m_effectEmitter->SetRotation(m_rotation);
	m_effectEmitter->Play();

	//�R���W�����I�u�W�F�N�g���쐬����B
	m_coll = NewGO<CollisionObject>(0);
	//����̃R���W�������쐬����B
	m_coll->CreateSphere(m_position, Quaternion::Identity, 35.0f * m_scale.z);

	//���O��player_fireball�ɂ���B
	m_coll->SetName("player_fireball");

	//�R���W�����I�u�W�F�N�g�������ō폜����Ȃ��悤�ɂ���B
	m_coll->SetIsEnableAutoDelete(false);

	return true;
}

void PlayerAttack::Update()
{
//�^�C�}�[�����Z����B
	m_timer += g_gameTime->GetFrameDeltaTime();
	
	if (m_timer > 1.0f) {
		//���W���ړ�������B
		m_position += m_moveSpeed * g_gameTime->GetFrameDeltaTime();
		
	}
	else {
		m_position = m_player->m_position;
		m_position.y += 50.0f;
	}
	
//�G�t�F�N�g�̍��W��ݒ肷��B
		m_effectEmitter->SetPosition(m_position);
		//�R���W�����I�u�W�F�N�g�ɍ��W��ݒ肷��B
		m_coll->SetPosition(m_position);

 	

	//�^�C�}�[��3.0f�ȏゾ������B
	 if (m_timer >= 3.0f)
	{
		m_player->m_ballView = false;
		//���g���폜����B
		DeleteGO(this);
	}
}