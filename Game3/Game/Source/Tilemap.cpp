#include "Tilemap.h"
#include "SpriteSheet.h"

Tilemap::Tilemap(fw::Mesh* mesh, fw::ShaderProgram* shader, fw::Texture* texture, SpriteSheet* spritesheet, vec2 scale) : m_pTileMesh(mesh), m_pTileShaderProgram(shader), m_pTileTexture(texture), m_pTileSpriteSheet(spritesheet), m_tileScale(scale)
, m_tileCount(0, 0)
{
	array_TileProps = new TileProperties[6]
	{
		TileProperties(spritesheet->GetSpriteName("crate_04"), false), //0 (Null)
		TileProperties(spritesheet->GetSpriteName("ground_05"), true), //1 (Concrete Floor)
		TileProperties(spritesheet->GetSpriteName("ground_06"), true), //2 (Grass Floor)
		TileProperties(spritesheet->GetSpriteName("crate_02"), false), //3 (Wooden Box)
		TileProperties(spritesheet->GetSpriteName("block_02"), false), //4 (Concrete Wall)
		TileProperties(spritesheet->GetSpriteName("crate_05"), false), //5 (Green Wall)
	};
}

Tilemap::~Tilemap()
{
	delete[] array_Tilemap;
}

void Tilemap::SetTilemap(unsigned char* tilemap, unsigned char rows, unsigned char columns)
{
	array_Tilemap = new unsigned char[rows * columns] {0};
	//std::copy(tilemap, &tilemap[rows * columns], array_Tilemap);
	m_tileCount.x = rows;
	m_tileCount.y = columns;

	for (unsigned char i = 0; i < columns; i++)
	{
		for (unsigned char j = 0; j < rows; j++)
		{
			array_Tilemap[i + (rows - j - 1) * columns] = tilemap[i + j * columns];
		}
	}
}

void Tilemap::Draw(vec2 projScale, vec2 cameraPos)
{
	
	for (size_t i = 0; i < m_tileCount.x * m_tileCount.y; i++)
	{
		int xCoord = i % (int)m_tileCount.x;
		int yCoord = i / (int)m_tileCount.y;

		TileProperties tp = array_TileProps[array_Tilemap[i]];
		
		m_pTileMesh->Draw(m_pTileShaderProgram, m_pTileTexture, projScale, cameraPos, m_tileScale, vec2(xCoord, yCoord) * m_tileScale + m_tileOffset, 0.0f, tp.blockInfo->spriteScale, tp.blockInfo->spriteOffset);
	}
}

bool Tilemap::GetIfWalkable(vec2 position)
{
	vec2 coOrd = (position - m_tileOffset) / m_tileScale;

	ImGui::Text("%d, %d, %d", (int)coOrd.x, (int)coOrd.y, (int)coOrd.x + (int)coOrd.y * (int)m_tileCount.x);
	if (coOrd.x < 0 || coOrd.y < 0 || coOrd.x >= m_tileCount.x || coOrd.y >= m_tileCount.y)
	{
		return true;
	}
	return array_TileProps[array_Tilemap[(int)coOrd.x + (int)coOrd.y * (int)m_tileCount.x]].WalkOn;
}
