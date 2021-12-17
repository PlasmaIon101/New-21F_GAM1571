#include "Framework.h"

#include "Pickup.h"

Pickup::Pickup(fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 position)
    : GameObject(pMesh, pShader, position)
{
}

Pickup::~Pickup()
{
}

void Pickup::Update(float deltaTime)
{
}
