#pragma once

#include "Framework.h"
#include "DataTypes.h"

class Tilemap;

class GameObject
{
public:
    GameObject(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos);
    GameObject(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::SpriteSheet* pSpriteSheet, vec2 pos);
    virtual ~GameObject();

    virtual void Update(float deltaTime);
    virtual void Draw(vec2 projScale, vec2 camPos);

    bool IsCollidingWith(GameObject* pOtherObject);

    void SetTexture(fw::Texture* pTexture) { m_pTexture = pTexture; }
    void SetTilemap(Tilemap* pTilemap) { m_pTilemap = pTilemap; }

    vec2 GetPosition();

protected:
    fw::Mesh* m_pMesh;
    fw::ShaderProgram* m_pShader;
    
    fw::Texture* m_pTexture;
    fw::SpriteSheet* m_pSpriteSheet;

    Tilemap* m_pTilemap;

    vec2 m_UVScale;
    vec2 m_UVOffset;

    vec2 m_Position;

    float m_Radius;
};
