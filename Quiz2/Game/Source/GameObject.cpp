#include "Framework.h"

#include "GameObject.h"

GameObject::GameObject(Game* pGame, fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 scale, vec2 pos)
    : m_pMesh( pMesh )
    , m_pShader( pShader )
    , m_Scale( scale )
    , m_Position( pos )
{

}

GameObject::~GameObject()
{
    delete com_Mesh;
    delete com_Position;
    delete com_Shader;
    delete com_Scale;
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::Draw(vec2 projScale, vec2 camPos)
{
    m_pMesh->Draw( m_pShader, nullptr, projScale, camPos, m_Scale, m_Position, vec2(1,1), vec2(0,0), 0.0f );
}
