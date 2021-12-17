#pragma once

#include "Framework.h"
#include "DataTypes.h"
#include "GameObject.h"

class PlayerController;
class Tilemap;

class Player : public GameObject
{
public:
    Player(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, PlayerController* pController, SpriteSheet* sheet);
    virtual ~Player();

    virtual void Update(float deltaTime) override;
    //virtual void Draw() override;

    void SetTilemap(Tilemap* tilemap);

protected:
    PlayerController* m_pPlayerController;

    Tilemap* m_pTilemap;
};
