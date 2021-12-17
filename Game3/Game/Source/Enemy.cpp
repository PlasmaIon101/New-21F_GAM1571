#include "Framework.h"
#include "Enemy.h"
#include "SpriteSheet.h"

Enemy::Enemy(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, SpriteSheet* sheet)
    : GameObject( pMesh, pShader, pTexture, pos, sheet)
{
    m_Sprite = sheet->GetSpriteName("crate_02");
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
}
