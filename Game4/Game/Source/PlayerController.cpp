#include "Framework.h"

#include "PlayerController.h"

PlayerController::PlayerController()
{
    m_OldFlags = 0;
    m_Flags = 0;
}

void PlayerController::StartFrame()
{
    m_OldFlags = m_Flags;
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
                if (pInputEvent->GetID() == 'W' || pInputEvent->GetID() == VK_UP)       { m_Flags |= Actions::Up; }
                if( pInputEvent->GetID() == 'S' || pInputEvent->GetID() == VK_DOWN )    { m_Flags |= Actions::Down; }
                if( pInputEvent->GetID() == 'A' || pInputEvent->GetID() == VK_LEFT )    { m_Flags |= Actions::Left; }
                if( pInputEvent->GetID() == 'D' || pInputEvent->GetID() == VK_RIGHT )   { m_Flags |= Actions::Right; }
                if( pInputEvent->GetID() == 'Z' )                                       { m_Flags |= Actions::Teleport; }
                if( pInputEvent->GetID() == VK_SPACE )                                  { m_Flags |= Actions::Push; }
                if( pInputEvent->GetID() == VK_SHIFT )                                  { m_Flags |= Actions::Pull; }
            }

            if( pInputEvent->GetInputState() == fw::InputState::Released )
            {
                if( pInputEvent->GetID() == 'W' || pInputEvent->GetID() == VK_UP )      { m_Flags &= ~Actions::Up; }
                if (pInputEvent->GetID() == 'S' || pInputEvent->GetID() == VK_DOWN)     { m_Flags &= ~Actions::Down; }
                if (pInputEvent->GetID() == 'A' || pInputEvent->GetID() == VK_LEFT)     { m_Flags &= ~Actions::Left; }
                if (pInputEvent->GetID() == 'D' || pInputEvent->GetID() == VK_RIGHT)    { m_Flags &= ~Actions::Right; }
                if (pInputEvent->GetID() == 'Z')                                        { m_Flags &= ~Actions::Teleport; }
                if (pInputEvent->GetID() == VK_SPACE)                                   { m_Flags &= ~Actions::Push; }
                if (pInputEvent->GetID() == VK_SHIFT)                                   { m_Flags &= ~Actions::Pull; }
            }
        }
    }
}

bool PlayerController::IsHeld(Actions action)
{
    return m_Flags & action;
}

bool PlayerController::WasPressed(Actions action)
{
    bool wasHeldLastFrame = m_OldFlags & action;
    bool isheldThisFrame = m_Flags & action;

    return wasHeldLastFrame == false && isheldThisFrame == true;
}

bool PlayerController::WasReleased(Actions action)
{
    bool wasHeldLastFrame = m_OldFlags & action;
    bool isheldThisFrame = m_Flags & action;

    return wasHeldLastFrame == true && isheldThisFrame == false;
}
