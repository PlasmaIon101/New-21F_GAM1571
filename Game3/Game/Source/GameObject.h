#pragma once

#include "Framework.h"
#include "DataTypes.h"

class SpriteSheet;

struct BlockInfo;

class GameObject
{
public:
    GameObject(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, SpriteSheet* sheet);
    virtual ~GameObject();

    virtual void Update(float deltaTime);
    virtual void Draw(vec2 projScale, vec2 camPos);

    vec2 GetPosition();

    bool IsCollidingWith(GameObject* pOtherObject);

    void SetTexture(fw::Texture* pTexture) { m_pTexture = pTexture; }

protected:
    fw::Mesh* m_pMesh;
    fw::ShaderProgram* m_pShader;
    fw::Texture* m_pTexture;

    SpriteSheet* m_SpriteSheet;
    BlockInfo* m_Sprite;
    vec2 m_Position;

    float m_Radius;
};
