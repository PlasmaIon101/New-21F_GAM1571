#pragma once

#include "Framework.h"
#include "DataTypes.h"
#include "ComponentBase.h"

class Game;

class GameObject
{
public:
    GameObject(Game* pGame, fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 scale, vec2 pos);
    virtual ~GameObject();

    virtual void Update(float deltaTime);
    virtual void Draw(vec2 projScale, vec2 camPos);

protected:
    // Rendering data.
    fw::Mesh* m_pMesh;
    fw::ShaderProgram* m_pShader;

    //Render - Pointers
    ComponentBase* com_Mesh;
    ComponentBase* com_Shader;

    // Transform data.
    vec2 m_Scale;
    vec2 m_Position;

    //Transform - Pointers
    ComponentBase* com_Scale;
    ComponentBase* com_Position;
};