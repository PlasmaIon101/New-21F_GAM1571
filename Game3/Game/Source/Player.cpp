#include "Framework.h"

#include "Player.h"
#include "PlayerController.h"
#include "SpriteSheet.h"
#include "Tilemap.h"

Player::Player(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, PlayerController* pController, SpriteSheet* sheet)
    : GameObject(pMesh, pShader, pTexture, pos, sheet)
    , m_pPlayerController(pController)
    , m_pTilemap(nullptr)
{
    m_Sprite = sheet->GetSpriteName("player_05");
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    float speed = 1.0f;
    vec2 delta = vec2(0, 0);

    if( m_pPlayerController->IsRightHeld() )
    {
        delta.x += speed * deltaTime;
    }
    if (m_pPlayerController->IsLeftHeld())
    {
        delta.x -= speed * deltaTime;
    }
    if (m_pPlayerController->IsUpHeld())
    {
        delta.y += speed * deltaTime;
    }
    if (m_pPlayerController->IsDownHeld())
    {
        delta.y -= speed * deltaTime;
    }
    if (m_pTilemap && m_pTilemap->GetIfWalkable(vec2(delta.x, 0) + m_Position))
    {
        m_Position += vec2(delta.x, 0);
    }
    if (m_pTilemap && m_pTilemap->GetIfWalkable(vec2(0, delta.y) + m_Position))
    {
        m_Position += vec2(0, delta.y);
    }
    ImGui::DragFloat( "Position X", &m_Position.x, 0.02f, -1.0f, 1.0f );
}

void Player::SetTilemap(Tilemap* tilemap)
{
    m_pTilemap = tilemap;
}
