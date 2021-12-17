#pragma once
#include "Math/Vector.h"

namespace fw
{
	class GameObject;

	enum class EventType { NOT_SET, Input, Collision, Destroy, GoToNextRound };
	enum class DeviceType { Keyboard, Mouse, };
	enum class InputState { Pressed, Release, };

	class Event
	{
	public:
		Event() {}
		virtual ~Event() {}
		virtual EventType GetEventType() = 0;
	};

	class GoToNextRound : public Event
	{
	public:
		GoToNextRound() {}
		virtual ~GoToNextRound() {}
		virtual EventType GetEventType() override { return EventType::GoToNextRound; }
	};


	class DestroyEvent : public Event
	{
	public:
		DestroyEvent(GameObject* first) : m_firstObject(first) {}
		virtual ~DestroyEvent() {}
		virtual EventType GetEventType() override { return EventType::Destroy; }

		GameObject* GetFirstObject() { return m_firstObject; }
	protected:
		GameObject* m_firstObject;
	};
	
	class CollisionEvent : public Event
	{
	public:
		CollisionEvent(GameObject* first, GameObject* second) : m_firstObject(first), m_secondObject(second) {}
		virtual ~CollisionEvent() {}
		virtual EventType GetEventType() override { return EventType::Collision; }

		GameObject* GetFirstObject() { return m_firstObject; }
		GameObject* GetSecondObject() { return m_secondObject; }
	protected:
		GameObject* m_firstObject;
		GameObject* m_secondObject;
	};

	class InputEvent : public Event
	{
	public:
		InputEvent(DeviceType deviceType, InputState keyState, int keyCode)
			: m_DeviceType(deviceType)
			, m_InputState(keyState)
			, m_ID(keyCode)
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
}