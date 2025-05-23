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
	m_modelRender.SetScale(Vector3(15.0f, 15.0f, 15.0f));//スケルトンモデルの拡大。

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
	OniAnim();//アニメーション
	OniState();
	Ray();//見えない光線を出して当たり判定をする関数

	m_alpha += g_gameTime->GetFrameDeltaTime() * 8.2f;
	m_spriteRender.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, fabsf(sinf(m_alpha))));

	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
	m_spriteRender.SetPosition(m_spPos);
	m_spriteRender.Update();
}
bool Oni::SearchPlayer() {
	Vector3 diff = { 0.0f,0.0f,0.0f };
	diff = m_player->m_position - m_position;//プレイヤーと鬼の距離を計算。
	//プレイヤーにある程度近かったら.。
	if (diff.LengthSq() <= 1700.0 * 1700.0f && m_player->m_position.y<20.0f)
	{
		//エネミーからプレイヤーに向かうベクトルを正規化する。
		diff.Normalize();
		//エネミーの正面のベクトルと、エネミーからプレイヤーに向かうベクトルの。
		//内積(cosθ)を求める。
		float cos = m_forward.Dot(diff);
		//内積(cosθ)から角度(θ)を求める。
		float angle = acosf(cos);
		//角度(θ)が7°より小さければ。
		if (angle <= (Math::PI / 180.0f) * 230.0f)
		{
			//プレイヤーを見つけた！。
			return true;
		}
	}
	//プレイヤーを見つけられなかった。
	return false;
}
bool Oni::SearchPlayerRays()
{
	Vector3 diff = { 0.0f,0.0f,0.0f };
	diff = m_player->m_position - m_position;//プレイヤーと鬼の距離を計算。
	//プレイヤーにある程度近かったら.。
	if (diff.LengthSq() <= 1500.0 * 1500.0f)
	{
		//エネミーからプレイヤーに向かうベクトルを正規化する。
		diff.Normalize();
		//エネミーの正面のベクトルと、エネミーからプレイヤーに向かうベクトルの。
		//内積(cosθ)を求める。
		float cos = m_forward.Dot(diff);
		//内積(cosθ)から角度(θ)を求める。
		float angle = acosf(cos);
		//角度(θ)が5°より小さければ。
		if (angle <= (Math::PI / 180.0f) * 5.0f)
		{
			//プレイヤーを見つけた！。
			return true;
		}
	}
	//プレイヤーを見つけられなかった。
	return false;
}

void Oni::haikai() {//徘徊と待機分けたほうがいいかも
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
		//重力を無くす。
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
	//鬼の前ベクトルを計算する。
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f){
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

void Oni::OniColl() {
		//被ダメアニメーチョン中及び死亡モーション中は処理をしない。
	if (m_OniState == 2 || m_OniState == 3) {
		return;
	}
	//プレイヤーの攻撃用のコリジョンを取得する。
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_fireball");
	//コリジョンの配列をfor文で回す。
	for (auto collision : collisions)
	{	

		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_charaCon))
		{
			if (m_collHitFlag == false) {
				//HPを1減らす。
				m_OniHP -= m_player->m_playerATK;
				//HPが0になったら。
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
				//プレイヤーに当たったら。
			if (covexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Player)
			{
				//フラグをtrueにする。
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
		//先にオブジェクトに当たっていたら。
		if (covexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Stage) {
			isHit = true;
			return 0.0f;
		}

		return 0.0f;
	}
};


void Oni::Ray() {//RayTestを使用してPlayerを視認するとダメージを与える。

	m_sphereCollider.Create(0.5f);//シェイプコライダークラスから球体を作る。
	btTransform start,startWall, end,endWall;//左からプレイヤー用Rayの起点,壁、オブジェ用Rayの起点，プレイヤー用終点、壁、オブジェ用の終点。
	start.setIdentity();//btTransform型の変数をbtVector型と同一性を持たせる。
	startWall.setIdentity();
	end.setIdentity();
	endWall.setIdentity();
	Vector3 endPos =m_forward;//
	endPos = m_player->m_position;

	//始点はエネミーの基点。
	start.setOrigin(btVector3(m_position.x, m_position.y+40.0f , m_position.z));
	startWall.setOrigin(btVector3(m_position.x, m_position.y + 75.0f, m_position.z));
	end.setOrigin(btVector3(endPos.x, m_position.y +40.0f, endPos.z));
	endWall.setOrigin(btVector3(endPos.x, m_position.y + 75.0f, endPos.z));

	SweepResultPlayer callback;//プレイヤー当たり判定用。
	SweepResultStage callbacks;//ステージ当たり判定用。

		//衝突検出。
		PhysicsWorld::GetInstance()->ConvexSweepTest((const btConvexShape*)m_sphereCollider.GetBody(), start, end, callback);
		PhysicsWorld::GetInstance()->ConvexSweepTest((const btConvexShape*)m_sphereCollider.GetBody(), startWall, endWall, callbacks);
		if (SearchPlayerRays() && callbacks.isHit == false /*&& callback.isHit == true*/) {
			//当たった。
			//スケルトンが死んだらプレイヤーにはダメージを与えないようにするためにreturnする。
			if (m_OniHP <= 0) {
				return;
			}
			m_player->m_playerHP -= 1;
			m_kei->Play(true);//警告音の再生。
			m_sininnFlag = true;//警告画像の表示用フラグ。
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

