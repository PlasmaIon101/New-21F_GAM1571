#pragma once

#include "Framework.h"

class PlayerController
{
public:
    enum Actions
    {
        Up = 1,
        Down = 2,
        Left = 4,
        Right = 8,
        Teleport = 16,
        Push = 32,
        Pull = 64,
    };
public:
    PlayerController();

    void StartFrame();
    void OnEvent(fw::Event* pEvent);

    bool IsHeld(Actions action);
    bool WasPressed(Actions action);
    bool WasReleased(Actions action);

protected:
    //bool m_OldUp;
    //bool m_OldDown;
    //bool m_OldLeft;
    //bool m_OldRight;
    //bool m_OldTeleport;
    //
    //bool m_Up;
    //bool m_Down;
    //bool m_Left;
    //bool m_Right;
    //bool m_Teleport;

    unsigned int m_OldFlags;
    unsigned int m_Flags;
};
