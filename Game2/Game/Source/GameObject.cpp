#include "Framework.h"

#include "GameObject.h"

GameObject::GameObject(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos)
    : m_pMesh( pMesh )
    , m_pShader( pShader )
    , m_pTexture( pTexture )
    , m_Position( pos )
    , m_Radius( 0.4f ) // TODO: Customize Radius.
{
}

GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::Draw(vec2 projScale, vec2 camPos)
{
    vec2 m_Scale = vec2( 1, 1 );

    m_pMesh->Draw( m_pShader, m_pTexture, projScale, camPos, m_Scale, m_Position, 0.0f );
}

bool GameObject::IsCollidingWith(GameObject* pOtherObject)
{
    assert( pOtherObject != nullptr );

    float distance = m_Position.DistanceTo( pOtherObject->m_Position );
    float combinedRadii = m_Radius + pOtherObject->m_Radius;

    if( distance < combinedRadii )
        return true;

    return false;
}
