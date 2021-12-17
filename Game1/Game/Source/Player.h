#pragma once

#include "Framework.h"
#include "DataTypes.h"
#include "GameObject.h"

class PlayerController;

class Player : public fw::GameObject
{
public:
	Player(fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 position, PlayerController* pControl);
	virtual ~Player();

	virtual void Update(float deltaTime) override;
	float Teleport(float x, float y); //Takes two randomly generated floats and uses it to generate you across the map.

protected:
	PlayerController* m_pControls;
};


