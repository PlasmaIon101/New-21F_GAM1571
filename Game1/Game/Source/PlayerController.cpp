#include "Framework.h"

#include "PlayerController.h"

PlayerController::PlayerController()
{
	m_MoveRight = false;
	m_MoveLeft = false;
	m_MoveUp = false;
	m_MoveDown = false;
    m_BulletTop = false;
    m_BulletTopRight = false;
    m_BulletRight = false;
    m_BulletBottomRight = false;
    m_BulletBottom = false;
    m_BulletBottomLeft = false;
    m_BulletLeft = false;
    m_BulletTopLeft = false;
}

void PlayerController::OnEvent(fw::Event* pEvent)
{
    if (pEvent->GetEventType() == fw::EventType::Input)
    {
        fw::InputEvent* pInputEvent = static_cast<fw::InputEvent*>(pEvent);

        if (pInputEvent->GetDeviceType() == fw::DeviceType::Keyboard)
        {
            if (pInputEvent->GetInputState() == fw::InputState::Pressed)
            {
                //Movement controls
                if (pInputEvent->GetID() == VK_RIGHT) { m_MoveRight = true; }
                if (pInputEvent->GetID() == VK_LEFT) {m_MoveLeft = true;}
                if (pInputEvent->GetID() == VK_UP) {m_MoveUp = true;}
                if (pInputEvent->GetID() == VK_DOWN) {m_MoveDown = true;}

                //Fire a bullet
                if (pInputEvent->GetID() == 'W') { m_BulletTop = true; }
                if (pInputEvent->GetID() == 'A') { m_BulletLeft = true; }
                if (pInputEvent->GetID() == 'S') { m_BulletRight = true; }
                if (pInputEvent->GetID() == 'D') { m_BulletLeft = true; }
                if (pInputEvent->GetID() == 'I') { m_BulletTopRight = true; }
                if (pInputEvent->GetID() == 'J') { m_BulletTopLeft = true; }
                if (pInputEvent->GetID() == 'K') { m_BulletBottomLeft = true; }
                if (pInputEvent->GetID() == 'L') { m_BulletBottomRight = true; }
            }
            else if (pInputEvent->GetInputState() == fw::InputState::Release)
            {
                if (pInputEvent->GetID() == VK_RIGHT) { m_MoveRight = false; }
                if (pInputEvent->GetID() == VK_LEFT) { m_MoveLeft = false; }
                if (pInputEvent->GetID() == VK_UP) { m_MoveUp = false; }
                if (pInputEvent->GetID() == VK_DOWN) { m_MoveDown = false; }

                if (pInputEvent->GetID() == 'W') { m_BulletTop = false; }
                if (pInputEvent->GetID() == 'A') { m_BulletLeft = false; }
                if (pInputEvent->GetID() == 'S') { m_BulletRight = false; }
                if (pInputEvent->GetID() == 'D') { m_BulletLeft = false; }
                if (pInputEvent->GetID() == 'I') { m_BulletTopRight = false; }
                if (pInputEvent->GetID() == 'J') { m_BulletTopLeft = false; }
                if (pInputEvent->GetID() == 'K') { m_BulletBottomLeft = false; }
                if (pInputEvent->GetID() == 'L') { m_BulletBottomRight = false; }
            }
        }


    }
}

bool PlayerController::IsRightHeld()
{
    return m_MoveRight;
}

bool PlayerController::IsLeftHeld()
{
    return m_MoveLeft;
}

bool PlayerController::IsUpHeld()
{
    return m_MoveUp;
}

bool PlayerController::IsDownHeld()
{
    return m_MoveDown;
}

bool PlayerController::IsWHeld()
{
    return m_BulletTop;
}

bool PlayerController::IsAHeld()
{
    return m_BulletLeft;
}

bool PlayerController::IsSHeld()
{
    return m_BulletRight;
}

bool PlayerController::IsDHeld()
{
    return false;
}

bool PlayerController::IsIHeld()
{
    return false;
}

bool PlayerController::IsJHeld()
{
    return false;
}

bool PlayerController::IsKHeld()
{
    return false;
}

bool PlayerController::IsLHeld()
{
    return false;
}
