#pragma once
#include "GameObject.h"

class Pickup : public fw::GameObject
{
public:
	Pickup(fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 position);
	virtual ~Pickup();

	virtual void Update(float deltaTime) override;
protected:

};
