#include "CoreHeaders.h"
#include "EventManager.h"
#include "Event.h"
#include "GameCore.h"

namespace fw{
	EventManager::EventManager()
	{
	}

	EventManager::~EventManager()
	{
		Event* pEvent = m_EventQueue.front();
		m_EventQueue.pop();

		delete pEvent;
	}

	void EventManager::AddEvent(Event* pEvent)
	{
		m_EventQueue.push(pEvent);

	}

	void EventManager::ProcessEvents(GameCore& pGameCore)
	{
		while (m_EventQueue.empty() == false)
		{
			Event* pEvent = m_EventQueue.front();
			m_EventQueue.pop();

			pGameCore.OnEvent(pEvent);

			delete pEvent;
		}
	}

}



