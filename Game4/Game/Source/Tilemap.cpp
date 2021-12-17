#include "Framework.h"

#include "Tilemap.h"
#include "Game.h"

Tilemap::Tilemap(Game* pGame, const TileType* pLayout, ivec2 layoutSize, vec2 tileSize)
	: m_LayoutSize( layoutSize )
	, m_TileSize( tileSize )
	, m_pMesh( nullptr )
	, m_pSpriteSheet( nullptr )
{
	m_pMesh = pGame->GetMesh( "Tile" );
	m_pShader = pGame->GetShader();
	m_pSpriteSheet = pGame->GetSpriteSheet();

	// Setup the tile properties.
	AddTileProperty( false, "", false );        //TT_Empty,
	AddTileProperty( true, "ground_05", true ); //TT_Grass,
	AddTileProperty( true, "ground_06", true ); //TT_Stone,
	AddTileProperty( true, "ground_01", true ); //TT_Dirt,
	AddTileProperty( true, "crate_02", false, true ); //TT_Box,

	// Copy the layout.
	m_pLayout = new TileType[layoutSize.x * layoutSize.y];
	//for( int i=0; i<layoutSize.x * layoutSize.y; i++ )
	//{
	//	m_pLayout[i] = pLayout[i];
	//}

	// Flip the layout as we copy.
	for( int y=0; y<m_LayoutSize.y; y++ )
	{
		for( int x=0; x<m_LayoutSize.x; x++ )
		{
			int index = y*m_LayoutSize.x + x;
			int flippedIndex = (m_LayoutSize.y - y - 1)*m_LayoutSize.x + x;

			m_pLayout[flippedIndex] = pLayout[index];
		}
	}

	m_PushableTilemap.push_back(ivec2(3, 3));
}

Tilemap::~Tilemap()
{
}

void Tilemap::Draw(vec2 projScale, vec2 camPos)
{
	ImGui::Begin("x");
	ImGui::Text("Tile Position (Pushable): %d, %d", deleteMe.x, deleteMe.y);
	ImGui::End();
	for( int y=0; y<m_LayoutSize.y; y++ )
	{
		for( int x=0; x<m_LayoutSize.x; x++ )
		{
			int index = y*m_LayoutSize.x + x;

			if( m_TileProperties[ m_pLayout[index] ].hasSprite )
			{
				vec2 pos( x*m_TileSize.x, y*m_TileSize.y );
				vec2 uvScale = m_TileProperties[ m_pLayout[index] ].uvScale;
				vec2 uvOffset = m_TileProperties[ m_pLayout[index] ].uvOffset;

				m_pMesh->Draw( m_pShader, m_pSpriteSheet->GetTexture(), projScale, camPos,
					m_TileSize, pos, uvScale, uvOffset, 0.0f );
			}
		}
	}

	for (size_t i = 0; i < m_PushableTilemap.size(); i++)
	{
		vec2 pos(m_PushableTilemap[i].x * m_TileSize.x, m_PushableTilemap[i].y * m_TileSize.y);
		vec2 uvScale = m_TileProperties[TT_Box].uvScale;
		vec2 uvOffset = m_TileProperties[TT_Box].uvOffset;

		m_pMesh->Draw(m_pShader, m_pSpriteSheet->GetTexture(), projScale, camPos,
			m_TileSize, pos, uvScale, uvOffset, 0.0f);
	}
}

bool Tilemap::IsWorldPositionWalkable(vec2 worldPos)
{
	worldPos -= vec2(0.5f, 0.0f);
	if( worldPos.x < 0 || worldPos.y < 0 ||
		worldPos.x >= m_LayoutSize.x*m_TileSize.x || worldPos.y >= m_LayoutSize.y*m_TileSize.y )
	{
		return false;
	}

	ivec2 tilePos = ivec2( (int)(worldPos.x/m_TileSize.x), (int)(worldPos.y/m_TileSize.y) );
	
	int tileIndex = tilePos.y * m_LayoutSize.x + tilePos.x;
	for (size_t i = 0; i < m_PushableTilemap.size(); i++)
	{
		int boxIndex = m_PushableTilemap[i].x + m_PushableTilemap[i].y * m_LayoutSize.x;
		if (boxIndex == tileIndex)
		{
			return false;
		}
	}
	TileType type = m_pLayout[tileIndex];

	return m_TileProperties[type].walkable;
}

bool Tilemap::IsIndexWalkable(int index)
{
	int x = index % m_LayoutSize.x;
	int y = index / m_LayoutSize.x;
	if (index < 0 || x >= m_LayoutSize.x || y >= m_LayoutSize.y)
	{
		return false;
	}
	for (size_t i = 0; i < m_PushableTilemap.size(); i++)
	{
		int boxIndex = m_PushableTilemap[i].x + m_PushableTilemap[i].y * m_LayoutSize.x;
		if (boxIndex == index)
		{
			return false;
		}
	}
	return m_TileProperties[m_pLayout[index]].walkable;
}

void Tilemap::TryPush(vec2 location)
{
	ivec2 playerLocation = ivec2((int)((location.x) / m_TileSize.x), (int)((location.y) / m_TileSize.y));
	for (size_t i = 0; i < m_PushableTilemap.size(); i++)
	{
		ivec2 newDirection = m_PushableTilemap[i] - playerLocation;
		newDirection.Normalize();
		if (playerLocation.x == m_PushableTilemap[i].x || playerLocation.y == m_PushableTilemap[i].y)
		{
			if (IsWorldPositionWalkable(vec2(m_PushableTilemap[i].x + newDirection.x, m_PushableTilemap[i].y + newDirection.y)))
			{
				m_PushableTilemap[i] += newDirection;
			}
		}
	}
}

void Tilemap::TryPull(vec2 location)
{
	ivec2 playerLocation = ivec2((int)((location.x) / m_TileSize.x), (int)((location.y) / m_TileSize.y));
	for (size_t i = 0; i < m_PushableTilemap.size(); i++)
	{
		ivec2 newDirection = m_PushableTilemap[i] - playerLocation;
		newDirection.Normalize();
		if (playerLocation.x == m_PushableTilemap[i].x || playerLocation.y == m_PushableTilemap[i].y)
		{
			if (IsWorldPositionWalkable(vec2(m_PushableTilemap[i].x + newDirection.x, m_PushableTilemap[i].y + newDirection.y)))
			{
				m_PushableTilemap[i] -= newDirection;
			}
		}
	}
}

void Tilemap::AddTileProperty(bool hasSprite, std::string name, bool walkable, bool push)
{
	vec2 uvScale(1,1);
	vec2 uvOffset(0,0);

	if( hasSprite )
	{
		uvScale = m_pSpriteSheet->GetSpriteByName( name ).uvScale;
		uvOffset = m_pSpriteSheet->GetSpriteByName( name ).uvOffset;
	}

	m_TileProperties.push_back( { hasSprite, uvScale, uvOffset, walkable, push } );
}
