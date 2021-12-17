#pragma once

#include "Framework.h"
#include "DataTypes.h"

class ComponentBase
{
public:
    ComponentBase() {};
    virtual ~ComponentBase() {};
};

class Renderable : public ComponentBase
{
public:
    fw::Mesh* m_pMeshComponent;
    fw::ShaderProgram* m_pShaderComponent;
};

class Transform : public ComponentBase
{
public:
    vec2 m_ScaleComponent;
    vec2 m_PositionComponent;
};