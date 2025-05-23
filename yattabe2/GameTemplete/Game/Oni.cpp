#include "stdafx.h"
#include "Oni.h"
#include "Player.h"
#include "time.h"
#include "Game.h"
#include "physics/Physics.h"
#include <physics/CharacterController.cpp>
#include "sound/SoundEngine.h"
#include "collision/CollisionObject.h"

Oni::Oni() {
	
}

Oni::~Oni() {
	DeleteGO(m_Bossbgm);
	DeleteGO(m_kei);
}

bool Oni::Start()
{
	m_animationClips[m_enAnimClip_Idle].Load("Assets/MrYoshinagaPresentsAssets/SkeletonAnim/SkeletonIdle.tka");
	m_animationClips[m_enAnimClip_Idle].SetLoopFlag(true);
	m_animationClips[m_enAnimClip_Attack].Load("Assets/MrYoshinagaPresentsAssets/SkeletonAnim/SkeletonAttack.tka");
	m_animationClips[m_enAnimClip_Attack].SetLoopFlag(true);
	m_animationClips[m_enAnimClip_Damage].Load("Assets/MrYoshinagaPresentsAssets/SkeletonAnim/SkeletonDamage.tka");
	m_animationClips[m_enAnimClip_Damage].SetLoopFlag(false);
	m_animationClips[m_enAnimClip_Desth].Load("Assets/MrYoshinagaPresentsAssets/SkeletonAnim/SkeletonDeath.tka");
	m_animationClips[m_enAnimClip_Desth].SetLoopFlag(false);
	m_animationClips[m_enAnimClip_Walk].Load("Assets/MrYoshinagaPresentsAssets/SkeletonAnim/SkeletonWalk.tka");
	m_animationClips[m_enAnimClip_Walk].SetLoopFlag(true);
	srand(time(NULL));
	zahyo1 = rand() % 1200 - 600;
	zahyo2 = rand() % 1200 - 600;
	

	m_modelRender.Init("Assets/MrYoshinagaPresentsAssets/Skeleton/Skeleton.tkm", m_animationClips, m_enAnimClip_Num, enModelUpAxisZ);
	m_player = FindGO<Player>("player");
	m_game = FindGO<Game>("game");

	m_spriteRender.Init("Assets/myfaile/sininn.DDS", 1920, 1080);
	m_spriteRender.SetScale(Vector3(0.3, 0.3, 1.0f));
	
	m_position = { (float)zahyo1,1800.0f,1800.0f };
	m_modelRender.SetPosition(m_position);

	m_rot.SetRotationDegY(180);
	m_modelRender.SetRotation(m_rot);
	m_modelRender.SetScale(Vector3(15.0f, 15.0f, 15.0f));//�X�P���g�����f���̊g��B

	g_soundEngine->ResistWaveFileBank(0, "Assets/SoundBGMfile/LastBoss.wav");
	m_Bossbgm = NewGO<SoundSource>(0,"LastBOss");
	m_Bossbgm->Init(0);

	g_soundEngine->ResistWaveFileBank(10, "Assets/SoundBGMfile/kei.wav");
	m_kei = NewGO<SoundSource>(0,"keikokuonn");
	m_kei->Init(10);
	
	m_charaCon.Init(35.0f, 70.0f, m_position);
	return true;
}

void Oni::Update() {
	
	if (SearchPlayer() == true) {
		Tuiseki();
	}
	else {
		haikai();
	}

	Rotation();
	OniColl();
	OniAnim();//�A�j���[�V����
	OniState();
	Ray();//�����Ȃ��������o���ē����蔻�������֐�

	m_alpha += g_gameTime->GetFrameDeltaTime() * 8.2f;
	m_spriteRender.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, fabsf(sinf(m_alpha))));

	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
	m_spriteRender.SetPosition(m_spPos);
	m_spriteRender.Update();
}
bool Oni::SearchPlayer() {
	Vector3 diff = { 0.0f,0.0f,0.0f };
	diff = m_player->m_position - m_position;//�v���C���[�ƋS�̋������v�Z�B
	//�v���C���[�ɂ�����x�߂�������.�B
	if (diff.LengthSq() <= 1700.0 * 1700.0f && m_player->m_position.y<20.0f)
	{
		//�G�l�~�[����v���C���[�Ɍ������x�N�g���𐳋K������B
		diff.Normalize();
		//�G�l�~�[�̐��ʂ̃x�N�g���ƁA�G�l�~�[����v���C���[�Ɍ������x�N�g���́B
		//����(cos��)�����߂�B
		float cos = m_forward.Dot(diff);
		//����(cos��)����p�x(��)�����߂�B
		float angle = acosf(cos);
		//�p�x(��)��7����菬������΁B
		if (angle <= (Math::PI / 180.0f) * 230.0f)
		{
			//�v���C���[���������I�B
			return true;
		}
	}
	//�v���C���[���������Ȃ������B
	return false;
}
bool Oni::SearchPlayerRays()
{
	Vector3 diff = { 0.0f,0.0f,0.0f };
	diff = m_player->m_position - m_position;//�v���C���[�ƋS�̋������v�Z�B
	//�v���C���[�ɂ�����x�߂�������.�B
	if (diff.LengthSq() <= 1500.0 * 1500.0f)
	{
		//�G�l�~�[����v���C���[�Ɍ������x�N�g���𐳋K������B
		diff.Normalize();
		//�G�l�~�[�̐��ʂ̃x�N�g���ƁA�G�l�~�[����v���C���[�Ɍ������x�N�g���́B
		//����(cos��)�����߂�B
		float cos = m_forward.Dot(diff);
		//����(cos��)����p�x(��)�����߂�B
		float angle = acosf(cos);
		//�p�x(��)��5����菬������΁B
		if (angle <= (Math::PI / 180.0f) * 5.0f)
		{
			//�v���C���[���������I�B
			return true;
		}
	}
	//�v���C���[���������Ȃ������B
	return false;
}

void Oni::haikai() {//�p�j�Ƒҋ@�������ق�����������
	if (m_OniState == 2 || m_OniState == 3) {
		return;
	}
	
	if (m_IsOnGroundFlag != true) {
		m_Bossbgm->Play(true);
		m_moveSpeed.y -= m_Rakka;
	}
	
	if (m_charaCon.GetPosition().y<=1.0f)
	{
		m_IsOnGroundFlag = true;
		//�d�͂𖳂����B
		m_moveSpeed.y = 0.0f;
		DeleteGO(m_Bossbgm);

		if (zahyo3 > 80) {
			m_moveSpeed.x += 20.0f;
			m_time += g_gameTime->GetFrameDeltaTime();
			if (m_time > 0.7f) {
				m_time = 0.0f;
				zahyo3 = rand() % 100;
			}
		}
		else if (zahyo3 > 60) {
			m_moveSpeed.x -= 20.0f;
			m_time += g_gameTime->GetFrameDeltaTime();
			if (m_time > 0.7f) {
				m_time = 0.0f;
				zahyo3 = rand() % 100;
			}
		}
		else if (zahyo3 > 40) {
			m_moveSpeed.z += 20.0f;
			m_time += g_gameTime->GetFrameDeltaTime();
			if (m_time > 0.7f) {
				m_time = 0.0f;
				zahyo3 = rand() % 100;
			}
		}
		else if (zahyo3 > 20) {
			m_moveSpeed.z -= 20.0f;
			m_time += g_gameTime->GetFrameDeltaTime();
			if (m_time > 0.7f) {
				m_time = 0.0f;
				zahyo3 = rand() % 100;
			}
		}
		else  {
			m_moveSpeed = { 0.0f,0.0f,0.0f };
			m_time += g_gameTime->GetFrameDeltaTime();
			if (m_time > 1.2f) {
				m_time = 0.0f;
				zahyo3 = rand() % 100;
			}
		}
	}

	if (fabsf(m_moveSpeed.x) < 0.001f && fabsf(m_moveSpeed.z) < 0.001f) {
		m_OniState = 0;
	}
	else {
		m_OniState = 1;
	}

		m_moveSpeed * 250.0f;
		m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
		
	}

void Oni::Tuiseki() {
	if (m_OniState == 2 || m_OniState == 3) {
		return;
	}
	Vector3 diff = m_player->m_position - m_position;
	if (m_OniHP <= 0) {
			return;
		}
	if (Oni::SearchPlayer() == true&&m_IsOnGroundFlag==true) {
		diff.Normalize();
		m_moveSpeed = diff;
		m_position = m_charaCon.Execute(m_moveSpeed, 3.0f);
		m_OniState = 1;
	}
	m_tuisekiFlag = true;
}

void Oni::Rotation() {
	//�S�̑O�x�N�g�����v�Z����B
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f){
		//m_moveSpeed.x��m_moveSpeed.z�̐�Βl���Ƃ���0.001�ȉ��Ƃ������Ƃ́B
		//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
		return;
	}
	//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
	//m_moveSpeed.x / m_moveSpeed.z�̌��ʂ�tan�ƂɂȂ�B
	//atan2���g�p���āA�p�x�����߂Ă���B
	//���ꂪ��]�p�x�ɂȂ�B
	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂ŁB
	//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
	m_rot.SetRotationY(-angle);

	//��]��ݒ肷��B
	m_modelRender.SetRotation(m_rot);

	m_forward = Vector3::AxisZ;
	m_rot.Apply(m_forward);

}

void Oni::OniColl() {
		//��_���A�j���[�`�������y�ю��S���[�V�������͏��������Ȃ��B
	if (m_OniState == 2 || m_OniState == 3) {
		return;
	}
	//�v���C���[�̍U���p�̃R���W�������擾����B
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_fireball");
	//�R���W�����̔z���for���ŉ񂷁B
	for (auto collision : collisions)
	{	

		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_charaCon))
		{
			if (m_collHitFlag == false) {
				//HP��1���炷�B
				m_OniHP -= m_player->m_playerATK;
				//HP��0�ɂȂ�����B
				if (m_OniHP <= 0)
				{
					m_OniHP = 0;
					m_OniState = 2;
				}
				else {
					m_OniState = 3;
				}
				m_collHitFlag = true;
			}
		}
	}
}

void Oni::OniState() {
	switch (m_OniState) {
	case 0:
		break;
	case 1:
		break;
	case 2:
		SuteHen();
		break;
	case 3:
		SuteHen();
		break;
	}
}

void Oni::SuteHen() {
	if (m_modelRender.IsPlayingAnimation() == false) {
		m_OniState = 0;
		m_collHitFlag = false;
	}
}
void Oni::OniAnim() {
	switch (m_OniState) {
		case 0:
			m_modelRender.PlayAnimation(m_enAnimClip_Idle);
			break;
		case 1:
			m_modelRender.PlayAnimation(m_enAnimClip_Walk);
			break;
		case 2:
			m_modelRender.PlayAnimation(m_enAnimClip_Desth);
			m_sininnFlag = false;
			if (m_modelRender.IsPlayingAnimation() == false) {
				m_game->m_CreaFlag = true;
			}
			break;
		case 3:
			m_modelRender.PlayAnimation(m_enAnimClip_Damage);
			break;
	}
	
}

struct SweepResultPlayer :public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;

	virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& covexResult, bool normalInWorldSpace)
	{
				//�v���C���[�ɓ���������B
			if (covexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player)
			{
				//�t���O��true�ɂ���B
				isHit = true;
				return 0.0f;
			}
			return 0.0f;
		
	}
};
struct SweepResultStage :public btCollisionWorld::ConvexResultCallback
{
	bool isHit = false;

	virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& covexResult, bool normalInWorldSpace)
	{
		//��ɃI�u�W�F�N�g�ɓ������Ă�����B
		if (covexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Stage) {
			isHit = true;
			return 0.0f;
		}

		return 0.0f;
	}
};


void Oni::Ray() {//RayTest���g�p����Player�����F����ƃ_���[�W��^����B

	m_sphereCollider.Create(0.5f);//�V�F�C�v�R���C�_�[�N���X���狅�̂����B
	btTransform start,startWall, end,endWall;//������v���C���[�pRay�̋N�_,�ǁA�I�u�W�F�pRay�̋N�_�C�v���C���[�p�I�_�A�ǁA�I�u�W�F�p�̏I�_�B
	start.setIdentity();//btTransform�^�̕ϐ���btVector�^�Ɠ��ꐫ����������B
	startWall.setIdentity();
	end.setIdentity();
	endWall.setIdentity();
	Vector3 endPos =m_forward;//
	endPos = m_player->m_position;

	//�n�_�̓G�l�~�[�̊�_�B
	start.setOrigin(btVector3(m_position.x, m_position.y+40.0f , m_position.z));
	startWall.setOrigin(btVector3(m_position.x, m_position.y + 75.0f, m_position.z));
	end.setOrigin(btVector3(endPos.x, m_position.y +40.0f, endPos.z));
	endWall.setOrigin(btVector3(endPos.x, m_position.y + 75.0f, endPos.z));

	SweepResultPlayer callback;//�v���C���[�����蔻��p�B
	SweepResultStage callbacks;//�X�e�[�W�����蔻��p�B

		//�Փˌ��o�B
		PhysicsWorld::GetInstance()->ConvexSweepTest((const btConvexShape*)m_sphereCollider.GetBody(), start, end, callback);
		PhysicsWorld::GetInstance()->ConvexSweepTest((const btConvexShape*)m_sphereCollider.GetBody(), startWall, endWall, callbacks);
		if (SearchPlayerRays() && callbacks.isHit == false /*&& callback.isHit == true*/) {
			//���������B
			//�X�P���g�������񂾂�v���C���[�ɂ̓_���[�W��^���Ȃ��悤�ɂ��邽�߂�return����B
			if (m_OniHP <= 0) {
				return;
			}
			m_player->m_playerHP -= 1;
			m_kei->Play(true);//�x�����̍Đ��B
			m_sininnFlag = true;//�x���摜�̕\���p�t���O�B
			if (m_player->m_playerHP <= 0) {
				m_player->m_playerHP = 0;
			}
			return;
		}
		else {
			m_sininnFlag = false;
			m_kei->Pause();
		}
}

void Oni::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
	if (m_sininnFlag == true) {
		m_spriteRender.Draw(rc);
	}
}

