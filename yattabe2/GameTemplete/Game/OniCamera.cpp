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
	//�v���C���[�̃C���X�^���X��T���B
	m_player = FindGO<Player>("player");
	m_oni = FindGO<Oni>("oni");
	m_game = FindGO<Game>("game");

	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	//m_toCameraPos.Set(0.0f, 125.0f, -600.0f);//�����w�肵���l���^�[�Q�b�g���痣���悤�ɂȂ�B
	//���_�ƒ����Ă�񂪈ꏏ�ɂȂ�ƃG���[���N����BUnity�����̍��W���O�O�O�Ȃ̂ňꏏ�ɂȂ��Ă��܂����̂������B
	m_toCameraPos.Set(0.0f, -1800.0f, -255.0f);

	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ肷��B
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(30000.0f);

	return true;
}

void OniCamera::Update()
{
	//�J�������X�V�B
	//�����_���v�Z����B
	Vector3 target = m_oni->m_position;
	//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B
	target.y += 80.0f;
	Vector3 toCameraPosOld = m_toCameraPos;
	
	//���_���v�Z����B
	Vector3 pos = target + m_toCameraPos;	
	
	//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
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
	//�J�����̍X�V�B
	g_camera3D->Update();
}
