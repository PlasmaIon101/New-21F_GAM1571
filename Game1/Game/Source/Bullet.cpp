#include "Framework.h"

#include "Bullet.h"
#include "PlayerController.h"

Bullet::Bullet(fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 position)
	: fw::GameObject(pMesh, pShader, position)
	, bulletDirection(0.0f, 0.0f)
{
}

Bullet::~Bullet()
{
}

void Bullet::Update(float deltaTime)
{
	float bulletSpeed = 40.0f;

	CheckBoundaries();

	m_Pos += bulletDirection * bulletSpeed * deltaTime;
}

void Bullet::SetDirection(vec2 direction)
{
	bulletDirection = direction;
}
