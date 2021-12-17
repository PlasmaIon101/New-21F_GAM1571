#pragma once

#include "Framework.h"
#include "DataTypes.h"

struct BlockInfo
{
	BlockInfo(vec2 scale, vec2 offset);
	vec2 spriteScale;
	vec2 spriteOffset;
};

class SpriteSheet
{
public:
	SpriteSheet(const char* name);
	~SpriteSheet();

	BlockInfo* GetSpriteName(const char* name);

protected:
	vec2 spriteDimension;
	std::map<std::string, BlockInfo*> spriteMap;
};
