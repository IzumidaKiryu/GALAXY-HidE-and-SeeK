#include "stdafx.h"
#include "Map.h"

#include "Player.h"
#include "Oni.h"

namespace {
	Vector3 MAP_SENTER_POSITION = Vector3(690.0f, -270.0f, 0.0f);

	float MAP_RADIUS = 2400.0f;
	float LIMITED_RANGE_IMAGE = 12000.0f;
}

Map::Map()
{
}

Map::~Map()
{
}

bool Map::Start()
{
	//�}�b�v�̍����摜�B
	m_spriteRender.Init("Assets/myfaile/map.DDS", 512, 512);
	m_spriteRender.SetPosition(MAP_SENTER_POSITION);

	//
	m_playerSprite.Init("Assets/myfaile/player.dds", 50, 50);
	m_playerSprite.SetPosition(MAP_SENTER_POSITION);

	//
	m_enemySprite.Init("Assets/myfaile/enemy.dds", 35, 35);

	m_oni = FindGO<Oni>("oni");
	m_player = FindGO<Player>("player");

	return true;
}

void Map::Update()
{
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"�x�{�^��|�}�b�v�\��/��\��");
	//�\������e�L�X�g��ݒ�B
	m_fontRender.SetText(wcsbuf);
	//�t�H���g�̈ʒu��ݒ�B
	m_fontRender.SetPosition(Vector3(250.0f, -400.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
	m_fontRender.SetScale(1.2f);
	//�t�H���g�̐F��ݒ�B
	m_fontRender.SetColor(g_vec4Yellow);

	Vector3 playerPosition = m_player->m_position;
	Vector3 enemhyPosition = m_oni->m_position;

	Vector3 mapPosition;

	if (g_pad[0]->IsTrigger(enButtonY)&&m_activeMap==false) {
		m_activeMap = true;
	}
	else if (g_pad[0]->IsTrigger(enButtonY) && m_activeMap == true) {
		m_activeMap = false;
	}

	if (WorldPositionConvertToMapPosition(playerPosition, enemhyPosition, mapPosition))
	{
		//�\������悤�ɐݒ�B
		m_isImage = true;
		//SpriteRender�ɍ��W��ݒ�B
		m_enemySprite.SetPosition(mapPosition);
	}
	else {
		m_isImage = false;
	}

	m_spriteRender.Update();
	m_playerSprite.Update();
	m_enemySprite.Update();
}

const bool Map::WorldPositionConvertToMapPosition(Vector3 worldCenterPosition, Vector3 worldPosition, Vector3& mapPosition)
{
	//Y�̓}�b�v�Ɗ֌W�Ȃ��̂�0�Œ�B
	worldCenterPosition.y = 0.0f;
	worldPosition.y = 0.0f;
	Vector3 diff = worldPosition - worldCenterPosition;

	if (diff.LengthSq() >= LIMITED_RANGE_IMAGE * LIMITED_RANGE_IMAGE) {
		//�\�����Ȃ�����B
		return false;
	}

	//�x�N�g���̒������擾�B
	float length = diff.Length();

	//�J�����̑O��������N�I�[�^�j�I���𐶐��B
	Vector3 forward = g_camera3D->GetForward();
	Quaternion rot;
	rot.AddRotationDegY(atan2(-forward.x, forward.z));

	rot.Apply(diff);

	diff.Normalize();

	//�}�b�v�̑傫��/���������Ńx�N�g�����}�b�v���W�n�ɕϊ�����B
	diff *= length * MAP_RADIUS / LIMITED_RANGE_IMAGE/10.0f;

	mapPosition = Vector3(MAP_SENTER_POSITION.x + diff.x, MAP_SENTER_POSITION.y + diff.z,0.0f);
	return true;
}

void Map::Render(RenderContext& rc)
{
	if (m_activeMap == true) {
		m_spriteRender.Draw(rc);
		m_playerSprite.Draw(rc);
		if (m_isImage == false) {
			return;
		}
		m_enemySprite.Draw(rc);
	}
	else {
		m_fontRender.Draw(rc);
	}
}

