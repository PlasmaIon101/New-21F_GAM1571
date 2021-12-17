#include "CoreHeaders.h"

#include "Mesh.h"
#include "ShaderProgram.h"

namespace fw {
	Mesh::Mesh(GLenum primitiveType, std::vector<float>& coOrdinates)
		: m_VBO(0)
		, m_PrimitiveType(primitiveType)
	{
		const int numAttributeComponentsPerVertex = 5; // x, y, r, g, & b for each vertex.

		m_NumVerts = (int)coOrdinates.size() / numAttributeComponentsPerVertex;

		// Generate a buffer for our vertex attributes.
		glGenBuffers(1, &m_VBO); // m_VBO is a GLuint.

		// Set this VBO to be the currently active one.
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		// Copy our attribute data into the VBO.
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numAttributeComponentsPerVertex * m_NumVerts, &coOrdinates[0], GL_STATIC_DRAW);
	}

	Mesh::~Mesh()
	{
		// Release the memory.
		glDeleteBuffers(1, &m_VBO);
	}

	void Mesh::Draw(ShaderProgram* pShader, vec2 position, float time)
	{
		// Set this VBO to be the currently active one.
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		// Get the attribute variable’s location from the shader.
		// Describe the attributes in the VBO to OpenGL.
		GLint a_Position = glGetAttribLocation(pShader->GetProgram(), "a_Position");
		if (a_Position != -1)
		{
			glEnableVertexAttribArray(a_Position);
			glVertexAttribPointer(a_Position, 2, GL_FLOAT, GL_FALSE, 20, (void*)0);
		}

		GLint a_Colors = glGetAttribLocation(pShader->GetProgram(), "a_Colors");
		if (a_Colors != -1)
		{
			glEnableVertexAttribArray(a_Colors);
			glVertexAttribPointer(a_Colors, 3, GL_FLOAT, GL_FALSE, 20, (void*)8);
		}

		//Set up Uniforms
		glUseProgram(pShader->GetProgram());

		GLint u_Offset = glGetUniformLocation(pShader->GetProgram(), "u_Offset");
		glUniform2f(u_Offset, position.x, position.y);

		GLint u_Size = glGetUniformLocation(pShader->GetProgram(), "u_Size");
		glUniform1f(u_Size, 2.0f);

		GLint u_Time = glGetUniformLocation(pShader->GetProgram(), "u_Time");
		//glUniform1f(u_Time);

		// Draw the primitive.
		glDrawArrays(m_PrimitiveType, 0, m_NumVerts);
	}
}
