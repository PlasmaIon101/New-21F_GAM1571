#pragma once

#include "Framework.h"
#include "DataTypes.h"
#include "GameObject.h"

class Enemy : public GameObject
{
public:
    Enemy(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, SpriteSheet* sheet);
    virtual ~Enemy();

    virtual void Update(float deltaTime) override;
    //virtual void Draw() override;

protected:
};
