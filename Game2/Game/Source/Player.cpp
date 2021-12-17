#include "Framework.h"

#include "Player.h"
#include "PlayerController.h"

Player::Player(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, PlayerController* pController)
    : GameObject( pMesh, pShader, pTexture, pos )
    , m_pPlayerController( pController )
{
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    float speed = 1.0f;

    if( m_pPlayerController->IsRightHeld() )
    {
        m_Position.x += speed * deltaTime;
    }

    ImGui::DragFloat( "Position X", &m_Position.x, 0.02f, -1.0f, 1.0f );
}
