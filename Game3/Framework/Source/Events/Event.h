#pragma once

#include "Math/Vector.h"

namespace fw {

enum class EventType { Input, Collision };
enum class DeviceType { Keyboard, Mouse };
enum class InputState { Pressed, Released };

class Event
{
public:
    Event() {}
    virtual ~Event() {}
    virtual EventType GetEventType() = 0;
};

class InputEvent : public Event
{
public:
    InputEvent(DeviceType deviceType, InputState inputState, int keyCode)
        : m_DeviceType( deviceType )
        , m_InputState( inputState )
        , m_ID( keyCode )
    {
    }

    virtual EventType GetEventType() override { return EventType::Input; }

    DeviceType GetDeviceType() { return m_DeviceType; }
    InputState GetInputState() { return m_InputState; }
    int GetID() { return m_ID; }
    vec2 GetPosition() { return m_Pos; }

protected:
    DeviceType m_DeviceType;
    InputState m_InputState;
    int m_ID;
    vec2 m_Pos;
};

} // namespace fw
