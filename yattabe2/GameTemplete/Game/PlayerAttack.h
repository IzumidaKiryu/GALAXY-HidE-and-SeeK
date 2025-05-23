#pragma once
#include "sound/SoundSource.h"
class Player;
class Oni;
class NokoriTime;
class PlayerAttack:public IGameObject
{
public:
	PlayerAttack();
	~PlayerAttack();

	bool Start();

	void Update();

	Player* m_Player=nullptr;

	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	
	SoundSource* m_bgm = nullptr;

	Player* m_player = nullptr;
	Oni* m_oni = nullptr;
	NokoriTime* m_time = nullptr;

private:
	Vector3					m_position = Vector3::Zero;			//���W�B
	Quaternion				m_rotation=Quaternion::Identity;	//��]�B
	Vector3					m_scale = Vector3::One;				//�傫���B
	Vector3					m_moveSpeed = Vector3::Zero;		//�ړ����x�B
	EffectEmitter* m_effectEmitter = nullptr;			        //�G�t�F�N�g�B
	float					m_timer = 0.0f;						//�^�C�}�[�B
	CollisionObject* m_coll = nullptr;
};

