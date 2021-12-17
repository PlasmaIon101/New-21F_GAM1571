#include "Framework.h"

#include "GameObject.h"

GameObject::GameObject(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos)
    : m_pMesh( pMesh )
    , m_pShader( pShader )
    , m_pTexture( pTexture )
    , m_pSpriteSheet( nullptr )
    , m_UVScale( 1,1 )
    , m_UVOffset( 0,0 )
    , m_Position( pos )
    , m_Radius( 0.4f ) // TODO: Customize Radius.
{
}

GameObject::GameObject(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::SpriteSheet* pSpriteSheet, vec2 pos)
    : m_pMesh( pMesh )
    , m_pShader( pShader )
    , m_pTexture( nullptr )
    , m_pSpriteSheet( pSpriteSheet )
    , m_UVScale( 1,1 )
    , m_UVOffset( 0,0 )
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

    if( m_pTexture )
    {
        m_pMesh->Draw( m_pShader, m_pTexture, projScale, camPos, m_Scale, m_Position, vec2(1,1), vec2(0,0), 0.0f );
    }
    else
    {
        m_pMesh->Draw( m_pShader, m_pSpriteSheet->GetTexture(), projScale, camPos, m_Scale, m_Position, m_UVScale, m_UVOffset, 0.0f );
    }
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

vec2 GameObject::GetPosition()
{
    return m_Position;
}
