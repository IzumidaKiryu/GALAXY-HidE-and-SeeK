#include "stdafx.h"
#include "Player.h"
#include "PlayerAttack.h"
#include "ItemSokudo.h"

#include "graphics/effect/EffectEmitter.h"
#include "collision/CollisionObject.h"
#include "sound/SoundEngine.h"


Player::Player() {	
}

Player::~Player() {
	DeleteGO(m_collisionObject);
	DeleteGO(m_bgm);
}

bool Player::Start()
{
	//�A�j���[�V�����N���b�v�����[�h����B
	m_animationClips[m_enAnimClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[m_enAnimClip_Idle].SetLoopFlag(true);
	m_animationClips[m_enAnimClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[m_enAnimClip_Walk].SetLoopFlag(true);
	m_animationClips[m_enAnimClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[m_enAnimClip_Jump].SetLoopFlag(false);
	m_animationClips[m_enAnimClip_Run].Load("Assets/animData/run.tka");
	m_animationClips[m_enAnimClip_Run].SetLoopFlag(true);
	m_modelRender.Init("Assets/modelData/unityChan.tkm", m_animationClips, m_enAnimClip_Num, enModelUpAxisY);
	m_modelRender.SetPosition(Vector3(0.0f, 0.0f, 0.0f));

	characterController.Init(25.0f, 75.0f, m_position);

	g_soundEngine->ResistWaveFileBank(3, "Assets/SoundBGMfile/main.wav");
	m_bgm = NewGO<SoundSource>(0,"main");
	m_bgm->Init(3);
	m_bgm->Play(true);

	m_collisionObject = NewGO<CollisionObject>(0, "player_col");//�R���W�����Ŏ���Ă݂悤

	colpos = m_position;
	colpos.y += 70.0f;
	//����̃R���W�������쐬����B
	m_collisionObject->CreateCapsule(colpos, Quaternion::Identity, 25.0f, 75.0f);
	m_collisionObject->SetName("player_col");
	m_collisionObject->SetPosition(m_position);
	////�R���W�����I�u�W�F�N�g�������ō폜����Ȃ��悤�ɂ���B
	m_collisionObject->SetIsEnableAutoDelete(false);
	m_collisionObject->GetbtCollisionObject().setUserIndex(enCollisionAttr_Player);//�����܂�
	m_modelRender.Update();
	return true;
}

void Player::Update() {
	Move();
	Rotetion();
	State();
	Anime();
	Attack();
	
	colpos = m_position;
	colpos.y += 70.0f;
	m_collisionObject->SetPosition(colpos);
	m_modelRender.Update();
}

void Player::Move() {
	m_moveSpeed.x = m_StartMoveSpeed.x;
	m_moveSpeed.z = m_StartMoveSpeed.z;
	//���X�e�B�b�N�̓��͗ʂ��擾�B
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//�J�����̑O�����ƉE�����̃x�N�g���������Ă���B
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y�����ɂ͈ړ������Ȃ��B
	forward.y = 0.0f;
	right.y = 0.0f;

	//���X�e�B�b�N�̓��͗ʂ�300.0f����Z�B
	right *= stickL.x *300.0f;
	forward *= stickL.y * 300.0f;

	//�ړ����x�ɃX�e�B�b�N�̓��͗ʂ����Z����&���������B
	m_moveSpeed += (right + forward)*=m_BaisokuCnt;
	if (g_pad[0]->IsPress(enButtonB)) {
		m_moveSpeed.x *= 3.0f;
		m_moveSpeed.z *= 3.0f;
	}
	//�n�ʂɕt���Ă�����B
	if (characterController.IsOnGround())
	{
		//�d�͂𖳂����B
		m_moveSpeed.y = 0.0f;
		m_jumpState = 0;
		//A�{�^���������ꂽ��B
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//�W�����v������B
			m_moveSpeed.y += 200.0f;
		}
	}
	//�n�ʂɕt���Ă��Ȃ�������B
	else
	{
		//A�{�^���������ꂽ��B
		if (g_pad[0]->IsTrigger(enButtonA) && m_jumpState == 0)
		{
			//�W�����v������B
			m_moveSpeed.y += 200.0f;
			m_jumpState = 1;
		}
		//�d�͂𔭐�������B
		m_moveSpeed.y -= 5.0f;
	}
	//�L�����N�^�[�R���g���[���[���g���č��W���ړ�������B
	m_position = characterController.Execute(m_moveSpeed, 1.0f / 60.0f);
	//�G�`������ɍ��W��������B
	m_modelRender.SetPosition(m_position);

}

void Player::Rotetion() {
	//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//�L�����N�^�[�̕�����ς���B
		m_rot.SetRotationYFromDirectionXZ(m_moveSpeed);
		//�G�`������ɉ�]��������B
		m_modelRender.SetRotation(m_rot);
	}

}

void Player::State() {
	if (characterController.IsOnGround() == false) {
		m_playerState = 1;
		return;
	}
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f) {
		if (g_pad[0]->IsPress(enButtonB)) {
			m_playerState = 3;
		}
		else {
			m_playerState = 2;
		}
	}

	else {
		m_playerState = 0;
	}
}

void Player::Anime() {

	//switch���B
	switch (m_playerState) {
		//�v���C���[�X�e�[�g��0(�ҋ@)��������B
	case 0:
		//�ҋ@�A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(m_enAnimClip_Idle);
		break;
		//�v���C���[�X�e�[�g��1(�W�����v��)��������B
	case 1:
		//�W�����v�A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(m_enAnimClip_Jump);
		break;
		//�v���C���[�X�e�[�g��2(����)��������B
	case 2:
		//�����A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(m_enAnimClip_Walk);
		break;
	case 3:
		m_modelRender.PlayAnimation(m_enAnimClip_Run);
		break;
	}

}

void Player::Attack() {
	if (g_pad[0]->IsTrigger(enButtonSelect)&&m_ballView==false) {
		m_plAtk = NewGO<PlayerAttack>(0, "platk");
		Vector3 AtkPos = m_position;
		AtkPos.y += 70.0f;
		m_plAtk->SetPosition(AtkPos);
		m_plAtk->SetRotation(m_rot);
		m_ballView = true;
	}
}

void Player::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}