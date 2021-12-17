#pragma once

#include "Framework.h"
#include "DataTypes.h"
#include "GameObject.h"

class PlayerController;

class Player : public GameObject
{
public:
    Player(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, PlayerController* pController);
    Player(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::SpriteSheet* pSpriteSheet, vec2 pos, PlayerController* pController);
    virtual ~Player();

    virtual void Update(float deltaTime) override;

protected:
    PlayerController* m_pPlayerController;

    ivec2 m_direction;
};
