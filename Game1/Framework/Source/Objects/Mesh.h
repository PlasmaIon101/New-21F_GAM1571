#pragma once

#include "Math/Vector.h"

namespace fw {

class ShaderProgram;

class Mesh
{
public:
	Mesh(GLenum primitiveType, std::vector<float>& coOrdinates);
	virtual ~Mesh();

	virtual void Draw(ShaderProgram* pShader, vec2 position, float time);
protected:
	GLuint m_VBO;
	GLenum m_PrimitiveType;
	int m_NumVerts;
};

}

