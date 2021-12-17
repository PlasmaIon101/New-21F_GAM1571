#include "CoreHeaders.h"

#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture.h"

namespace fw {

Mesh::Mesh(GLenum primitiveType, std::vector<VertexFormat>& verts)
    : m_VBO( 0 )
    , m_PrimitiveType( primitiveType )
{
    m_NumVerts = (int)verts.size();

    // Generate a buffer for our vertex attributes.
    glGenBuffers( 1, &m_VBO ); // m_VBO is a GLuint.

    // Set this VBO to be the currently active one.
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );

    // Copy our attribute data into the VBO.
    glBufferData( GL_ARRAY_BUFFER, sizeof(VertexFormat)*m_NumVerts, &verts[0], GL_STATIC_DRAW );
}

Mesh::~Mesh()
{
    // Release the memory.
    glDeleteBuffers( 1, &m_VBO );
}

void Mesh::SetupUniform(ShaderProgram* pShader, char* name, float value)
{
    GLint location = glGetUniformLocation( pShader->GetProgram(), name );
    glUniform1f( location, value );
}

void Mesh::SetupUniform(ShaderProgram* pShader, char* name, vec2 value)
{
    GLint location = glGetUniformLocation( pShader->GetProgram(), name );
    glUniform2f( location, value.x, value.y );
}

void Mesh::SetupAttribute(ShaderProgram* pShader, char* name, int size, GLenum type, GLboolean normalize, int stride, int64_t startIndex)
{
    GLint location = glGetAttribLocation( pShader->GetProgram(), name );
    if( location != -1 )
    {
        glEnableVertexAttribArray( location );
        glVertexAttribPointer( location, size, type, normalize, stride, (void*)startIndex );
    }
}

void Mesh::Draw(ShaderProgram* pShader, Texture* pTexture, vec2 projScale, vec2 camPos, vec2 scale, vec2 pos, float time)
{
    // Set this VBO to be the currently active one.
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );

    // Get the attribute variable’s location from the shader.
    // Describe the attributes in the VBO to OpenGL.
    SetupAttribute( pShader, "a_Position", 2, GL_FLOAT, GL_FALSE, 20, 0 );
    SetupAttribute( pShader, "a_Color", 4, GL_UNSIGNED_BYTE, GL_TRUE, 20, 8 );
    SetupAttribute( pShader, "a_UVCoord", 2, GL_FLOAT, GL_FALSE, 20, 12 );

    // Setup the uniforms.
    glUseProgram( pShader->GetProgram() );
    
    //vec2 camPos( -2.0f, 0 );

    // Transform uniforms.
    SetupUniform( pShader, "u_ObjectTranslation", pos );
    SetupUniform( pShader, "u_ObjectScale", vec2(1.0f, 1.0f) );
    SetupUniform( pShader, "u_CameraTranslation", -camPos );
    SetupUniform( pShader, "u_ProjectionScale", vec2(1/3.0f, 1/3.0f) );
    
    // Misc uniforms.
    SetupUniform( pShader, "u_Time", time );

    // Setup textures.
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, pTexture->GetTextureID() );

    // Draw the primitive.
    glDrawArrays( m_PrimitiveType, 0, m_NumVerts );
}

} // namespace fw
