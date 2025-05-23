#include "stdafx.h"
#include "TItlePlayer.h"
#include "Fead.h"


TItlePlayer::TItlePlayer()
{

}

TItlePlayer::~TItlePlayer()
{
}

bool TItlePlayer::Start()
{
	//アニメーションクリップをロードする。
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

	m_koko.Init("Assets/myfaile/kokodoko.DDS", 1920, 1080);
	m_mita.Init("Assets/myfaile/mita.DDS", 1920, 1080);

	m_fead = FindGO<Fead>("fead");

	characterController.Init(25.0f, 75.0f, m_position);

	m_modelRender.Update();
	return true;
}

void TItlePlayer::Update()
{
	m_counter += g_gameTime->GetFrameDeltaTime();

	if (m_counter > 5.0f&&m_loopFlag==false) {
		m_mitaFlag = true;
	}
	if (m_counter > 10.0f&&m_loopFlag==false) {//10秒たったら処理を終わらせてタイトル画像表示。
		m_flag = true;
		m_mitaFlag = false;
		return;
	}
	else {
		Move();
		Rotetion();
		Anime();
		State();
	}
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

void TItlePlayer::Move()
{
	if (characterController.IsOnGround())
	{
		//重力を無くす。
		m_moveSpeed.y = 0.0f;
		if (zahyo3 > 80) {
			m_moveSpeed.x += 20.0f;
			m_timer += g_gameTime->GetFrameDeltaTime();
			if (m_timer > 0.7f) {
				m_timer = 0.0f;
				zahyo3 = rand() % 100;
			}
		}
		else if (zahyo3 > 60) {
			m_moveSpeed.x -= 20.0f;
			m_timer += g_gameTime->GetFrameDeltaTime();
			if (m_timer > 0.7f) {
				m_timer = 0.0f;
				zahyo3 = rand() % 100;
			}
		}
		else if (zahyo3 > 40) {
			m_moveSpeed.z += 20.0f;
			m_timer += g_gameTime->GetFrameDeltaTime();
			if (m_timer > 0.7f) {
				m_timer = 0.0f;
				zahyo3 = rand() % 100;
			}
		}
		else if (zahyo3 > 20) {
			m_moveSpeed.z -= 20.0f;
			m_timer += g_gameTime->GetFrameDeltaTime();
			if (m_timer > 0.7f) {
				m_timer = 0.0f;
				zahyo3 = rand() % 100;
			}
		}
		else {
			m_moveSpeed = { 0.0f,0.0f,0.0f };
			m_timer += g_gameTime->GetFrameDeltaTime();
			if (m_timer > 1.2f) {
				m_timer = 0.0f;
				zahyo3 = rand() % 100;
			}
		}
	}

	if (fabsf(m_moveSpeed.x) < 0.001f && fabsf(m_moveSpeed.z) < 0.001f) {
		m_playerState = 0;
	}
	else {
		m_playerState = 2;
	}

	m_moveSpeed *150.0f;
	m_position = characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

}

void TItlePlayer::Rotetion()
{
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下ということは。
		//このフレームではキャラは移動していないので旋回する必要はない。
		return;
	}
	//atan2はtanθの値を角度(ラジアン単位)に変換してくれる関数。
	//m_moveSpeed.x / m_moveSpeed.zの結果はtanθになる。
	//atan2を使用して、角度を求めている。
	//これが回転角度になる。
	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	//atanが返してくる角度はラジアン単位なので。
	//SetRotationDegではなくSetRotationを使用する。
	m_rot.SetRotationY(-angle);

	//回転を設定する。
	m_modelRender.SetRotation(m_rot);

	m_forward = Vector3::AxisZ;
	m_rot.Apply(m_forward);
}

void TItlePlayer::Anime()
{
	//switch文。
	switch (m_playerState) {
		//プレイヤーステートが0(待機)だったら。
	case 0:
		//待機アニメーションを再生する。
		m_modelRender.PlayAnimation(m_enAnimClip_Idle);
		break;
		//プレイヤーステートが1(ジャンプ中)だったら。
	case 1:
		//ジャンプアニメーションを再生する。
		m_modelRender.PlayAnimation(m_enAnimClip_Jump);
		break;
		//プレイヤーステートが2(歩き)だったら。
	case 2:
		//歩きアニメーションを再生する。
		m_modelRender.PlayAnimation(m_enAnimClip_Walk);
		break;
	case 3:
		m_modelRender.PlayAnimation(m_enAnimClip_Run);
		break;
	}
}

void TItlePlayer::State()
{
	if (fabsf(m_position.x) >= 0.001f || fabsf(m_position.z) >= 0.001f) {
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

void TItlePlayer::Render(RenderContext& rc)
{
	 if (m_mitaFlag == true) {
		m_mita.Draw(rc);
	}
	 else if (m_counter < 5.0f) {
		 m_koko.Draw(rc);
	 }

	m_modelRender.Draw(rc);
}
