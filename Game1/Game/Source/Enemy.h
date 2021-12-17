#pragma once

#include "Framework.h"
#include "DataTypes.h"
#include "GameObject.h"


class Enemy : public fw::GameObject
{
public:
	Enemy(fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 position, int enemyType);
	virtual ~Enemy();

	virtual void Update(float deltaTime) override;
protected:
	int enemyType;
};
