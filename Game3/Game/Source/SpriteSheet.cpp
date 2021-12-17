#include "Framework.h"
#include "SpriteSheet.h"
#include "../Libraries/rapidjson/document.h"

SpriteSheet::SpriteSheet(const char* name)
{
    //const char* jsonString = fw::LoadCompleteFile("Data/Textures/Sokoban.json", nullptr);
    const char* jsonString = fw::LoadCompleteFile(name, nullptr);
    rapidjson::Document document;
    document.Parse(jsonString);
    delete[] jsonString;

    rapidjson::Value& spriteToolVersion = document["SpriteTool"];
    int version = spriteToolVersion.GetInt();

    if (document.HasMember("Width"))
    {
        int width = document["Width"].GetInt();
        spriteDimension.x = width;
    }

    if (document.HasMember("Height"))
    {
        int height = document["Height"].GetInt();
        spriteDimension.y = height;
    }

    rapidjson::Value& spriteArray = document["Sprites"];
    for (rapidjson::SizeType i = 0; i < spriteArray.Size(); i++)
    {
        rapidjson::Value& sprite = spriteArray[i];

        float x = (float)(sprite["X"].GetInt());
        float y = (float)(sprite["Y"].GetInt());
        float width = (float)(sprite["W"].GetInt());
        float height = (float)(sprite["H"].GetInt());
        std::string spriteName = sprite["Name"].GetString();
        spriteMap[spriteName] = new BlockInfo(vec2(width, height) / spriteDimension, vec2(x, y) / spriteDimension);
    }
}

SpriteSheet::~SpriteSheet()
{
}

BlockInfo* SpriteSheet::GetSpriteName(const char* name)
{
    return spriteMap[name];
}

BlockInfo::BlockInfo(vec2 scale, vec2 offset)
{
    spriteScale = scale;
    spriteOffset = offset;

}
