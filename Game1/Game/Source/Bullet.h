#pragma once

#include "Framework.h"
#include "DataTypes.h"
#include "GameObject.h"

class Bullet : public fw::GameObject
{
public:
	Bullet(fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 position);
	virtual ~Bullet();

	virtual void Update(float deltaTime) override;

	void SetDirection(vec2 direction);
protected:
	vec2 bulletDirection;
};
