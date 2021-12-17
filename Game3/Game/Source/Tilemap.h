#pragma once

#include "Framework.h"
#include "DataTypes.h"

struct BlockInfo;
class SpriteSheet;

enum class TileMapping
{
    Null, //0
	Path_Grass, //1
	Path_Concrete, //2
	Object_Box, //3
	Wall_Brick, //4
	Wall_Steel, //5
};

struct TileProperties
{
	TileProperties(BlockInfo* information, bool walkable) : blockInfo(information), WalkOn(walkable) {};

	BlockInfo* blockInfo;
	bool WalkOn;
};

class Tilemap
{
public:
	Tilemap(fw::Mesh* mesh, fw::ShaderProgram* shader, fw::Texture* texture, SpriteSheet* spritesheet, vec2 scale);
	~Tilemap();

	void SetTilemap(unsigned char* tilemap, unsigned char rows, unsigned char columns);

	void Draw(vec2 projScale, vec2 cameraPos);

	bool GetIfWalkable(vec2 position);

protected:
	fw::ShaderProgram* m_pTileShaderProgram;
	fw::Mesh* m_pTileMesh;
	SpriteSheet* m_pTileSpriteSheet;
	fw::Texture* m_pTileTexture;
	vec2 m_tileScale;
	vec2 m_tileOffset;

	TileProperties* array_TileProps;
	
	vec2 m_tileCount;

	unsigned char* array_Tilemap;
};
