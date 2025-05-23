#pragma once
class Fead;
class TItlePlayer:public IGameObject
{
public:
	TItlePlayer();
	~TItlePlayer();

	bool Start()override;
	void Update();
	void Move();
	void Rotetion();
	void Anime();
	void State();
	void Render(RenderContext& rc);

	enum EnAnimationClip {
		m_enAnimClip_Idle,
		m_enAnimClip_Walk,
		m_enAnimClip_Jump,
		m_enAnimClip_Run,
		m_enAnimClip_Num,
	};

	Vector3 m_position = Vector3::Zero;
	Vector3 m_moveSpeed = Vector3::Zero;
	Vector3 m_StartMoveSpeed = { 0.0f,0.0f,0.0f };
	Vector3	m_forward = Vector3::AxisZ;

	ModelRender m_modelRender;
	Quaternion m_rot = Quaternion::Identity;
	AnimationClip m_animationClips[m_enAnimClip_Num];
	SpriteRender m_koko;
	SpriteRender m_mita;

	int m_playerState = 0;
	int m_jumpState = 0;
	int zahyo3 = 0;


	float m_timer = 0.0f;
	float m_counter = 0.0f;
	float m_alpha = 1.0f;

	bool m_mitaFlag = false;
	bool m_flag = false;
	bool m_loopFlag = false;
	
	CharacterController characterController;

	Fead* m_fead = nullptr;
};

