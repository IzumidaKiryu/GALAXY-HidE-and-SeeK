#pragma once
#include "sound/SoundSource.h"
class Player;
class Game;

class Oni : public IGameObject{
public:
	Oni();
	~Oni();
	bool Start();
	void Update();
	void haikai();
	void Tuiseki();
	void Rotation();
	void OniState();
	void OniAnim();
	void Ray();
	void OniColl();
	void SuteHen();
	void Render(RenderContext& rc);
	bool SearchPlayer();
	bool SearchPlayerRays();

	//メンバ変数。
	ModelRender m_modelRender;
	Quaternion m_rot =Quaternion::Identity;
	Vector3 m_position = Vector3::Zero;
	Vector3 m_moveSpeed = Vector3::Zero;
	Vector3 m_Hit = Vector3::Zero;//Rayが当たったオブジェクトの座標を格納する変数。
	Vector3	m_forward = Vector3::AxisZ;	//エネミーの正面ベクトル。
	Vector3 m_spPos = { 0.0f,300.0f,0.0f };
	SphereCollider m_sphereCollider;
	CharacterController m_charaCon;
	SpriteRender m_spriteRender;
	
	bool m_DeathFlag = false;
	bool m_IsOnGroundFlag = false;
	bool m_collHitFlag = false;
	bool m_sininnFlag = false;
	bool m_tuisekiFlag = false;


	int zahyo1=0;//敵の初期配置用ランダム数値。
	int zahyo2=0; 
	int zahyo3=0; 
	int m_OniHP=10;
	int m_OniMaxHP = m_OniHP;
	int m_OniState = 0;

	float m_time = 0.0f;
	float m_Rakka=8.2f;
	float m_stime = 0.0f;
	float m_alpha = 1.0f;
	
	Player* m_player=nullptr;
	Game* m_game=nullptr;
	SoundSource* m_Bossbgm=nullptr;
	SoundSource* m_kei = nullptr;
	
	enum EnAnimationClip {
		m_enAnimClip_Attack,
		m_enAnimClip_Damage,
		m_enAnimClip_Desth,
		m_enAnimClip_Idle,
		m_enAnimClip_Walk,
		m_enAnimClip_Num,
	};
	AnimationClip m_animationClips[m_enAnimClip_Num];
};




