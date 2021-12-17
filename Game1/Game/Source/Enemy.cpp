#include "Framework.h"

#include "Enemy.h"

Enemy::Enemy(fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 position, int enemyType)
    : GameObject(pMesh, pShader, position)
    , enemyType(enemyType)
{
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
    float enemyOneSpeed = 2.0f;

    CheckBoundaries();
    
    if (enemyType == 1)
    {
        m_Pos.x += enemyOneSpeed * deltaTime;
    }

    if (enemyType == 2)
    {
        m_Pos.x -= enemyOneSpeed * deltaTime;
    }

    if (enemyType == 3)
    {
        m_Pos.y += enemyOneSpeed * deltaTime;
    }

    if (enemyType == 4)
    {
        m_Pos.y -= enemyOneSpeed * deltaTime;
    }
}
