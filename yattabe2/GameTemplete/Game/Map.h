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
	/// ワールド座標系からマップ座標系に変換。
	/// </summary>
	/// <param name="worldCenterPosition">マップの中心とするオブジェクトのワールド座標。</param>
	/// <param name="worldPosition">マップに表示したいオブジェクトのワールド座標。</param>
	/// <param name="mapPosition">変換した後のマップ座標。</param>
	/// <returns>マップに表示する座標ならtrue。</returns>
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

