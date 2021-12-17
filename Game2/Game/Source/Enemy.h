#pragma once

#include "Framework.h"
#include "DataTypes.h"
#include "GameObject.h"

class Enemy : public GameObject
{
public:
    Enemy(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos);
    virtual ~Enemy();

    virtual void Update(float deltaTime) override;
    //virtual void Draw() override;

protected:
};

void Allocate(int size)
{
    float* arrayOfFloats = new float[size];

    delete[] arrayOfFloats;
}

void ExampleTwo(int n)
{

}



class Shape
{
public:
    Shape();
    ~Shape();
    float GetArea();
};

class Rectangle : public Shape
{
public:
    Rectangle();
    ~Rectangle();
};