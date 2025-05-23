#pragma once
class Player;
class Oni;
class Map :public IGameObject
{
public:
	Map();
	~Map();

	bool Start();
	void Update();

	void Render(RenderContext& rc);

private:
	/// <summary>
	/// ���[���h���W�n����}�b�v���W�n�ɕϊ��B
	/// </summary>
	/// <param name="worldCenterPosition">�}�b�v�̒��S�Ƃ���I�u�W�F�N�g�̃��[���h���W�B</param>
	/// <param name="worldPosition">�}�b�v�ɕ\���������I�u�W�F�N�g�̃��[���h���W�B</param>
	/// <param name="mapPosition">�ϊ�������̃}�b�v���W�B</param>
	/// <returns>�}�b�v�ɕ\��������W�Ȃ�true�B</returns>
	const bool WorldPositionConvertToMapPosition(Vector3 worldCenterPosition, Vector3 worldPosition, Vector3& mapPosition);
	SpriteRender				m_spriteRender;
	SpriteRender				m_playerSprite;
	SpriteRender				m_enemySprite;

	Player* m_player = nullptr;
	Oni* m_oni = nullptr;
	bool m_isImage = false;

	bool m_activeMap = false;

	FontRender m_fontRender;
};

