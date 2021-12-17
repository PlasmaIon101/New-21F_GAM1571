#include "Framework.h"

#include "Player.h"
#include "PlayerController.h"
#include "Tilemap.h"

Player::Player(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, PlayerController* pController)
    : GameObject( pMesh, pShader, pTexture, pos )
    , m_pPlayerController( pController )
{
}

Player::Player(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::SpriteSheet* pSpriteSheet, vec2 pos, PlayerController* pController)
    : GameObject( pMesh, pShader, pSpriteSheet, pos )
    , m_pPlayerController( pController )
{
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    float speed = 5.0f;

    vec2 newPos = m_Position;

    // Try moving up/down.
    if( m_pPlayerController->IsHeld(PlayerController::Actions::Up) )
    {
        newPos.y += speed * deltaTime;
        m_direction = ivec2(0, 1);
    }
    if( m_pPlayerController->IsHeld(PlayerController::Actions::Down) )
    {
        newPos.y -= speed * deltaTime;
        m_direction = ivec2(0, -1);
    }

    if( m_pTilemap->IsWorldPositionWalkable( newPos + vec2(0.0f, -0.5f) ) &&
        m_pTilemap->IsWorldPositionWalkable( newPos + vec2(0.0f, 0.0f) ) &&
        m_pTilemap->IsWorldPositionWalkable( newPos + vec2(0.0f, 0.0f) ) &&
        m_pTilemap->IsWorldPositionWalkable( newPos + vec2(0.0f, 0.0f) ) )
    {
        m_Position = newPos;
    }

    // Try moving left/right.
    newPos = m_Position;
    if( m_pPlayerController->IsHeld(PlayerController::Actions::Left) )
    {
        newPos.x -= speed * deltaTime;
        m_direction = ivec2(-1, 0);
    }
    if( m_pPlayerController->IsHeld(PlayerController::Actions::Right) )
    {
        newPos.x += speed * deltaTime;
        m_direction = ivec2(1, 0);
    }

    if( m_pTilemap->IsWorldPositionWalkable( newPos + vec2(0.2f, 0.1f) ) &&
        m_pTilemap->IsWorldPositionWalkable( newPos + vec2(0.8f, 0.1f) ) &&
        m_pTilemap->IsWorldPositionWalkable( newPos + vec2(0.2f, 0.3f) ) &&
        m_pTilemap->IsWorldPositionWalkable( newPos + vec2(0.8f, 0.3f) ) )
    {
        m_Position = newPos;
    }

    if (m_pPlayerController->WasPressed(PlayerController::Actions::Teleport))
    {
        m_Position = vec2(rand() / (float)RAND_MAX * 15, rand() / (float)RAND_MAX * 15);
    }

    if (m_pPlayerController->WasPressed(PlayerController::Actions::Push))
    {
        m_pTilemap->TryPush(m_Position);
    }

    if (m_pPlayerController->WasPressed(PlayerController::Actions::Pull))
    {
        m_pTilemap->TryPull(m_Position);
    }

    if( m_pSpriteSheet )
    {
        fw::SpriteSheet::SpriteInfo info = m_pSpriteSheet->GetSpriteByName( "player_06" );
        m_UVScale = info.uvScale;
        m_UVOffset = info.uvOffset;
    }
}
