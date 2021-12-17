#include "Framework.h"

#include "Player.h"
#include "PlayerController.h"

Player::Player(fw::Mesh* pMesh, fw::ShaderProgram* pShader, vec2 position, PlayerController* pControl)
    : GameObject(pMesh, pShader, position)
    , m_pControls(pControl)
{
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    float playerSpeed = 30.0f;

    CheckBoundaries();

    if (m_pControls->IsRightHeld())
    {
        m_Pos.x += playerSpeed * deltaTime;
    }

    if (m_pControls->IsLeftHeld())
    {
        m_Pos.x -= playerSpeed * deltaTime;
    }

    if (m_pControls->IsUpHeld())
    {
        m_Pos.y += playerSpeed * deltaTime;
    }

    if (m_pControls->IsDownHeld())
    {
        m_Pos.y -= playerSpeed * deltaTime;
    }
    
    ImGui::DragFloat("Position X", &m_Pos.x, 0.02f, -1.0f, 1.0f);
    ImGui::DragFloat("Position Y", &m_Pos.y, 0.02f, -1.0f, 1.0f);
    
    //m_Size -= deltaTime;
}

float Player::Teleport(float x, float y)
{
    return 0.0f;
}
