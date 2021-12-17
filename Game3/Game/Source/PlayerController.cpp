#include "PlayerController.h"

PlayerController::PlayerController()
{
    m_Right = false;
    m_Down = false;
    m_Left = false;
    m_Up = false;
}

void PlayerController::OnEvent(fw::Event* pEvent)
{
    if( pEvent->GetEventType() == fw::EventType::Input )
    {
        fw::InputEvent* pInputEvent = static_cast<fw::InputEvent*>( pEvent );

        if( pInputEvent->GetDeviceType() == fw::DeviceType::Keyboard )
        {
            if( pInputEvent->GetInputState() == fw::InputState::Pressed )
            {
                if( pInputEvent->GetID() == 'W' || pInputEvent->GetID() == VK_UP )      { m_Up = true; }
                if( pInputEvent->GetID() == 'A' || pInputEvent->GetID() == VK_LEFT )    { m_Left = true; }
                if( pInputEvent->GetID() == 'S' || pInputEvent->GetID() == VK_DOWN )    { m_Down = true; }
                if( pInputEvent->GetID() == 'D' || pInputEvent->GetID() == VK_RIGHT )   { m_Right = true; }
            }

            if( pInputEvent->GetInputState() == fw::InputState::Released )
            {
                if( pInputEvent->GetID() == 'W' || pInputEvent->GetID() == VK_UP )      { m_Up = false; }
                if( pInputEvent->GetID() == 'A' || pInputEvent->GetID() == VK_LEFT )    { m_Left = false; }
                if( pInputEvent->GetID() == 'S' || pInputEvent->GetID() == VK_DOWN )    { m_Down = false; }
                if( pInputEvent->GetID() == 'D' || pInputEvent->GetID() == VK_RIGHT )   { m_Right = false; }
            }
        }
    }
}

bool PlayerController::IsRightHeld()
{
    return m_Right;
}

bool PlayerController::IsUpHeld()
{
    return m_Up;
}

bool PlayerController::IsLeftHeld()
{
    return m_Left;
}

bool PlayerController::IsDownHeld()
{
    return m_Down;
}
