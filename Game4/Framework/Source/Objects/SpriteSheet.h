#pragma once

#include "Math\Vector.h"

namespace fw {

class Texture;

class SpriteSheet
{
public:
    struct SpriteInfo
    {
        vec2 uvScale;
        vec2 uvOffset;
    };

public:
    SpriteSheet(const char* filename, Texture* pTexture);
    virtual ~SpriteSheet();

    Texture* GetTexture() { return m_pTexture; }

    SpriteInfo GetSpriteByName(std::string name);    

protected:
    std::map<std::string, SpriteInfo> m_Sprites;

    fw::Texture* m_pTexture;
};

} // namespace fw
